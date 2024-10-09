/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_redir_filltype.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 14:21:49 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/09 02:38:35 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string/parse.h>
#include <ft/string.h>
#include <msh/ast/lexer.h>
#include <msh/features.h>
#include <msh/log.h>
#include <stdlib.h>

#define ACCEPTABLE_REDIR_FOLLOWUPS " \t\n0123456789abcdefghijklmnopqrstuvwxyz\
ABCDEFGHIJKLMNOPQRSTUVWXYZ'\"$./~*?[]:,=+_%@!`"

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

const char	*msh_syntax_error_str(const char *c);
const char	*msh_syntax_error_char(char c);

static t_ast_error	msh_ast_redir_fill_lex(t_ast_token *token,
						t_ast_lexer *state, size_t *inc)

{
	t_ast_error	err;

	if (!*state->input)
		return (msh_ast_errd(AST_ERROR_SYNTAX, (void *)
				msh_syntax_error_str("newline"), false));
	err = msh_ast_tokenize(state);
	if (err.type != AST_ERROR_NONE)
		return (err);
	if (ft_lst_size(state->tokens) == 0)
		return (msh_ast_errd(AST_ERROR_SYNTAX, (void *)
				msh_syntax_error_str("newline"), false));
	token->value.redir.right_word = state->tokens;
	token->value.redir.state = REDIR_STATE_WORD;
	*inc += state->cursor;
	return (err);
}

const char	*msh_ast_strredir(t_ast_redir_type type);

static t_ast_error	msh_ast_redir_fill_lex_pre(t_ast_token *token,
						t_ast_lexer *state, size_t *inc, bool heredoc)
{
	const char		*input;
	t_ast_lexer		lexer;

	input = state->input + state->cursor + *inc;
	if (!ft_strchr(ACCEPTABLE_REDIR_FOLLOWUPS, *input))
		return (msh_ast_errd(AST_ERROR_SYNTAX, (void *)
				msh_syntax_error_char(*input), false));
	while (*input && ft_strchr(SEP_CHARS, *input))
	{
		input++;
		*inc += 1;
	}
	lexer = msh_ast_lexer_root(state->msh, input);
	lexer.allow_subst = !heredoc;
	lexer.discrim_mode = true;
	lexer.delim = SEP_CHARS "|&<>(";
	return (msh_ast_redir_fill_lex(token, &lexer, inc));
}

t_ast_error	msh_ast_redir_filltype(t_ast_token *token,
						t_ast_lexer *state, size_t *inc)
{
	t_ast_error				err;
	const bool				is_fd = token->kind == REDIR_FD_IN
		|| token->kind == REDIR_FD_OUT;
	const bool				is_heredoc = token->kind == REDIR_HEREDOC
		|| token->kind == REDIR_HEREDOC_STRIP;

	err = msh_ast_ok();
	msh_log(state->msh, MSG_DEBUG_TOKENIZER, "redir type: %s\n",
		msh_ast_strredir(token->kind));
	if (is_fd)
	{
		token->value.redir.right_fd = msh_redir_try_yoink_fd(state, NULL);
		if (token->value.redir.right_fd != -1)
			token->value.redir.state = REDIR_STATE_FD;
	}
	else
	{
		err = msh_ast_redir_fill_lex_pre(token, state, inc, is_heredoc);
	}
	return (err);
}
