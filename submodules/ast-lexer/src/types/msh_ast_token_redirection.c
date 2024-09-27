/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_redirection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:36:16 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/27 16:35:23 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string/parse.h>
#include <ft/string.h>
#include <msh/ast/lexer.h>
#include <msh/features.h>

static size_t	msh_ast_redir_len(t_ast_redir_type type)
{
	if (type < REDIR_FILE_CLOBBER)
		return (3);
	if (type < REDIR_FILE_IN)
		return (2);
	return (1);
}

static bool	msh_coerce_types(t_ast_redir_type type)
{
	if (FEAT_PARSER_BASH_REDIRS)
		return (true);
	if (type == REDIR_HERESTRING || type == REDIR_HEREDOC_STRIP
		|| type == REDIR_FILE_CLOBBER_A || type == REDIR_FILE_CLOBBER
		|| type == REDIR_FILE_OUT_A)
		return (false);
	if (FEAT_PARSER_42SH_REDIRS)
		return (true);
	if (type == REDIR_FD_IN || type == REDIR_FD_OUT)
		return (false);
	return (true);
}

static t_ast_redir_type	msh_ast_token_redirection_type(t_ast_lexer *state)
{
	static const char	*redirs[] = {
	[REDIR_HERESTRING] = "<<", [REDIR_HEREDOC_STRIP] = "<<-",
	[REDIR_FILE_CLOBBER_A] = "&>|", [REDIR_FILE_CLOBBER] = ">|",
	[REDIR_HEREDOC] = "<<", [REDIR_FILE_APPEND] = ">>", [REDIR_FILE_INOUT]
		= "<>", [REDIR_FD_IN] = "<&", [REDIR_FD_OUT] = ">&", [REDIR_FILE_OUT_A]
		= "&>", [REDIR_FILE_IN] = "<", [REDIR_FILE_OUT] = ">"
	};
	const char			*line = &state->input[state->cursor];
	size_t				n;

	if (!line || !*line)
		return (-1);
	n = 0;
	while (n < sizeof(redirs) / sizeof(*redirs))
	{
		if (!ft_strncmp(line, redirs[n], ft_strlen(redirs[n])))
			return (n);
		n++;
	}
	return (-1);
}

static long long	msh_redir_try_yoink_fd(t_ast_lexer *state, size_t *inc)
{
	const char		*line = &state->input[state->cursor + *inc];
	char			*newstr;
	size_t			size;
	long long		n;
	t_str_parseerr	err;

	if (!line || !*line)
		return (-1);
	size = ft_strcspn(line, DELIM_CHARS);
	newstr = ft_strndup(line, size);
	if (!newstr)
		return (-1);
	err = ft_strtoll(newstr, &n);
	free(newstr);
	if (err || n < 0)
		return (-1);
	*inc += size;
	return (n);
}

static t_ast_error	msh_ast_redir_filltype(t_ast_token *token,
						t_ast_lexer *state)
{
	t_ast_lexer	lexer;
	t_ast_error	err;

	err = msh_ast_ok();
	if (token->kind == REDIR_FD_IN || token->kind == REDIR_FD_OUT)
	{
		token->value.redir.right_fd = msh_redir_try_yoink_fd(state, NULL);
		if (token->value.redir.right_fd != -1)
			token->value.redir.state = REDIR_STATE_FD;
	}
	else
	{
		lexer = msh_ast_lexer_root(state->msh, state->input + state->cursor);
		err = msh_ast_tokenize(&lexer);
		if (err.type == AST_ERROR_NONE)
			token->value.redir.right_word = lexer.tokens->content;
		return (err);
	}
	return (msh_ast_ok());
}

t_ast_error	msh_ast_token_redirection(t_ast_lexer *state, t_ast_token **tokret,
				size_t *inc)
{
	t_ast_token			*token;
	t_ast_error			err;
	t_ast_redir_type	type;

	type = msh_ast_token_redirection_type(state);
	if ((int)type == -1 || !msh_coerce_types(type))
		return (msh_ast_errd(AST_ERROR_UNEXPECTED, "msh_ast_token_redirection"
				": invalid redirection type", false));
	err = msh_ast_token_new(TKN_REDIR, &token);
	if (err.type == AST_ERROR_NONE)
	{
		token->kind = type;
		token->value.redir.left_fd = -1;
		token->value.redir.right_fd = -1;
		*inc = msh_ast_redir_len(type);
		err = msh_ast_redir_filltype(token, state);
		if (err.type == AST_ERROR_NONE)
			*tokret = token;
	}
	return (err);
}
