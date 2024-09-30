/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_tokenize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:45:27 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/30 10:13:53 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <ft/print.h>
#include <ft/string.h>
#include <msh/ast/lexer.h>
#include <msh/features.h>
#include <msh/util.h>
#include <stdlib.h>

#define G FEAT_TOK_GROUP
#define DBG msh_ast_lexer_debug

#define LEXER_INPUT_ALLOC_ERR ": failed to allocate memory for command input"
#define TOKEN_NODE_ALLOC_ERR ": failed to allocate memory for token node"

#define UNEXPECTED_EOF "unexpected EOF while looking for matching `%c'"

bool		msh_ast_lexer_is_delim(t_ast_lexer *state, const char c);

static bool	msh_ast_is_redirection(t_ast_lexer *state)
{
	const char	*input = &state->input[state->cursor];
	const char	current = *input;
	char		next;

	if (!current)
		return (false);
	if (current == '<' || current == '>')
		return (true);
	next = input[1];
	if (current == '&' && (next == '>' || next == '<'))
		return (true);
	return (false);
}

/*
 What I would give to have proper macros
 Like this could've been 2 times shorter if we had the SIMPLEST of

 #define TRY(fn) do { \
	err = fn(state, token, inc); \
	if (err.type != AST_ERROR_CANCEL) \
		return (err); \
	} while (0);

 But no. Lenghty and verbose code it is.
*/

const char	*msh_syntax_error_char(const char c);

static t_ast_error	msh_ast_next_global_token(t_ast_lexer *state,
						t_ast_token **token, size_t *inc, const char *input)
{
	t_ast_error	err;

	if ((FEAT_TOK_PARAN && *input == ')') || (FEAT_TOK_GROUP && *input == '}'))
		return (msh_ast_errd(AST_ERROR_SYNTAX, (void *)
				msh_syntax_error_char(*input), false));
	err = msh_ast_token_keyword(state, token, inc);
	if (err.type != AST_ERROR_CANCEL)
		return (err);
	err = msh_ast_token_number(state, token, inc);
	if (err.type != AST_ERROR_CANCEL)
		return (err);
	if (FEAT_SCRIPTING && !ft_strncmp(input, ";;", 2))
		return (msh_ast_token_simple(TKN_SEMISEMI, token, inc, 2));
	else if (*input == '\n' || (FEAT_TOK_AND && !ft_strncmp(input, "&&", 2))
		|| (FEAT_TOK_OR && !ft_strncmp(input, "||", 2))
		|| (FEAT_JOB_CONTROL && *input == '&')
		|| (FEAT_TOK_SEMICOLON && *input == ';'))
		return (msh_ast_token_delim(state, token, inc));
	else if (*input == '|')
		return (msh_ast_token_simple(TKN_PIPE, token, inc, 1));
	return (msh_ast_token_word(state, token, inc));
}

static t_ast_error	msh_ast_next_token(t_ast_lexer *state, t_ast_token **token,
						size_t *inc)
{
	const char	*input = &state->input[state->cursor];

	*inc = 0;
	*token = NULL;
	DBG(state, "(%d) lookup at '%s'\n", state->id, input);
	if (*input != '\n' && (ft_strchr(state->ifs, *input)
			|| ft_strchr(SEP_CHARS, *input)))
		return (msh_ast_token_sep(state, token, inc));
	else if (msh_ast_is_substituable(state))
		return (msh_ast_token_substitution(state, token, inc));
	if (msh_ast_lexer_is_delim(state, '\"')
		|| (state->discrim_mode && !state->delim))
		return (msh_ast_token_word(state, token, inc));
	else if ((*input == '(' && FEAT_TOK_PARAN) || (*input == '{' && G))
		return (msh_ast_token_group(state, token, inc));
	else if (*input == '\'')
		return (msh_ast_token_single_quote(state, token, inc));
	else if (*input == '"')
		return (msh_ast_token_string(state, token, inc));
	else if (msh_ast_is_redirection(state))
		return (msh_ast_token_redirection(state, token, inc));
	else if (FEAT_SCRIPTING && *input == '#' && (state->cursor == 0
			|| ft_strchr(SEP_CHARS, state->input[state->cursor - 1])))
		return (msh_ast_token_comment(state, token, inc));
	return (msh_ast_next_global_token(state, token, inc, input));
}

#define ERROR_MSG_STR "[ERROR] %s (%s), recoverable: %s\n"
#define ERROR_MSG_CHR "[ERROR] %s (%c), recoverable: %s\n"

static t_ast_error	msh_ast_lexer_errors(t_ast_lexer *s, t_ast_error err)
{
	const size_t	len = ft_strlen(s->input);
	const char		*fmt = ERROR_MSG_STR;

	if (err.type != AST_ERROR_NONE)
	{
		if (err.type == AST_ERROR_UNEXPECTED_EOF)
			fmt = ERROR_MSG_CHR;
		DBG(s, fmt, msh_ast_strerror(err.type), err.data,
			msh_strbool(err.retry));
		return (err);
	}
	if (s->cursor > len)
	{
		DBG(s, "[WARN] Lexer's cursor was ahead of input (%d)\n", (int)len);
		s->cursor = len;
	}
	if (s->delim && !msh_ast_lexer_is_delim(s, s->input[s->cursor]))
	{
		DBG(s, "Delimiter '%s' not found, reprompting...\n", s->delim);
		return (msh_ast_errd(AST_ERROR_UNEXPECTED_EOF, (char *)s->delim, 1));
	}
	DBG(s, "Done matching, cursor: %d\n", (int) s->cursor);
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
		&& !msh_ast_lexer_is_delim(state, state->input[state->cursor]))
	{
		err = msh_ast_next_token(state, &token, &inc);
		if (err.type != AST_ERROR_NONE)
			break ;
		DBG(state, "(%d) Got: ", state->id);
		if (token && state->msh->flags.debug_tokenizer)
			msh_ast_token_print(state->msh, token);
		if (token && !ft_lst_tadd(&state->tokens, token))
			err = msh_ast_errd(AST_ERROR_ALLOC, TOKEN_NODE_ALLOC_ERR, false);
		state->cursor += ft_max(inc, 1);
	}
	err = msh_ast_lexer_errors(state, err);
	if (state->msh->forked || err.type != AST_ERROR_NONE)
		ft_lst_free(&state->tokens, (t_lst_dealloc) msh_ast_token_free);
	return (err);
}
