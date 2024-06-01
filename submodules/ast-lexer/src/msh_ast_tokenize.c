/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_tokenize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:45:27 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/01 20:18:06 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <ft/print.h>
#include <ft/string.h>
#include <msh/ast/lexer.h>
#include <stdlib.h>

#define EOF "unexpected EOF while looking for matching `%c'"
#define DBG msh_ast_lexer_debug

#define LEXER_INPUT_ALLOC_ERR ": failed to allocate memory for command input"
#define TOKEN_NODE_ALLOC_ERR ": failed to allocate memory for token node"

__attribute__((unused))
static bool	msh_is_string_substitution(t_ast_lexer *state, const char *input)
{
	const bool	in_string = state->delim == '\"';
	const char	next = input[1];

	if (next == 0)
		return (false);
	if (next == '(' || next == '{')
		return (true);
	if (in_string)
		return (false);
	return (next == '\'' || next == '\"');
}

static t_ast_error	msh_ast_next_global_token(t_ast_lexer *state,
						t_ast_token **token, size_t *inc, const char *input)
{
	if (!ft_strncmp(input, ";;", 2))
		return (msh_ast_token_simple(TKN_SEMISEMI, token, inc, 2));
	// else if (*input == '$' && !msh_is_string_substitution(state, input))
	// 	return (msh_ast_token_substitution(state, token, inc));
	else if (!ft_strncmp(input, "&&", 2) || !ft_strncmp(input, "||", 2)
		|| *input == ';' || *input == '\n')
		return (msh_ast_token_delim(state, token, inc));
	else if (*input == '|')
		return (msh_ast_token_simple(TKN_PIPE, token, inc, 1));
	else if (*input == '&')
		return (msh_ast_token_simple(TKN_AMP, token, inc, 1));
	return (msh_ast_token_word(state, token, inc));
}

static t_ast_error	msh_ast_next_token(t_ast_lexer *state, t_ast_token **token,
						size_t *inc)
{
	const char	*input = &state->input[state->cursor];

	*inc = 0;
	*token = NULL;
	DBG(state, "(%d) lookup at '%s'\n", state->id, input);
	if (*input == '\0')
		return (msh_ast_token_simple(TKN_EOF, token, inc, 0));
	else if (*input != '\n' && ft_strchr(SEP_CHARS, *input))
		return (msh_ast_token_sep(state, token, inc));
	// else if (*input == '$' && msh_is_string_substitution(state, input))
	// 	return (msh_ast_token_substitution(state, token, inc));
	else if (*input == '\'')
		return (msh_ast_token_single_quote(state, token, inc));
	//TODO: every token inside string
	if (state->delim == '\"')
		return (msh_ast_token_word(state, token, inc));
	else if (*input == '"')
		return (msh_ast_token_string(state, token, inc));
	else if (*input == '#' && (state->cursor == 0
			|| ft_strchr(SEP_CHARS, state->input[state->cursor - 1]))) //TODO: check if \n in sep chars is an issue
		return (msh_ast_token_comment(state, token, inc));
	return (msh_ast_next_global_token(state, token, inc, input));
}

static t_ast_error	msh_ast_lexer_errors(t_ast_lexer *state, t_ast_error err)
{
	const size_t	len = ft_strlen(state->input);

	if (err.type != AST_ERROR_NONE)
	{
		DBG(state, "[ERROR] %s (%s)\n", msh_ast_strerror(err.type), err.data);
		return (err);
	}
	if (state->cursor > len)
	{
		DBG(state, "[WARN] Lexer's cursor was ahead of input (%d)\n", (int)len);
		state->cursor = len;
	}
	if (state->delim != 0 && state->input[state->cursor] != state->delim)
	{
		DBG(state, "Delimiter '%c' not found, reprompting...\n", state->delim);
		return (msh_ast_errd(AST_ERROR_SYNTAX, "missing delimiter end", true));
	}
	DBG(state, "Done matching, cursor: %d\n", (int) state->cursor);
	return (msh_ast_ok());
}

t_ast_error	msh_ast_tokenize(t_ast_lexer *state)
{
	t_ast_error	err;
	t_ast_token	*token;
	size_t		inc;

	if (!state->input)
		return (msh_ast_errd(AST_ERROR_ALLOC, LEXER_INPUT_ALLOC_ERR, false));
	err = msh_ast_ok();
	while (err.type == AST_ERROR_NONE && state->cursor < ft_strlen(state->input)
		&& state->input[state->cursor] != state->delim)
	{
		err = msh_ast_next_token(state, &token, &inc);
		if (err.type != AST_ERROR_NONE)
			break ;
		DBG(state, "(%d) %s\n", state->id, msh_ast_strtoken(token->type));
		if (token && !ft_lst_tadd(&state->tokens, token))
			err = msh_ast_errd(AST_ERROR_ALLOC, TOKEN_NODE_ALLOC_ERR, false);
		state->cursor += ft_max(inc, 1);
	}
	err = msh_ast_lexer_errors(state, err);
	if (state->msh->forked || err.type != AST_ERROR_NONE)
		ft_lst_free(&state->tokens, (t_lst_dealloc) msh_ast_token_free);
	return (err);
}
