/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_redirection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:36:16 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/30 10:59:27 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string/parse.h>
#include <ft/string.h>
#include <msh/ast/lexer.h>
#include <msh/features.h>
#include <stdio.h>

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
	[REDIR_HERESTRING] = "<<<", [REDIR_HEREDOC_STRIP] = "<<-",
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

t_ast_error	msh_ast_redir_filltype(t_ast_token *token, t_ast_lexer *state,
				size_t *inc);

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
		token->value.redir.state = REDIR_STATE_UNSET;
		*inc = 1 + (type < REDIR_FILE_IN) + (type < REDIR_FILE_CLOBBER);
		err = msh_ast_redir_filltype(token, state, inc);
		*tokret = NULL;
		if (err.type == AST_ERROR_NONE)
			*tokret = token;
	}
	if (err.type != AST_ERROR_NONE)
		msh_ast_token_free(token);
	return (err);
}
