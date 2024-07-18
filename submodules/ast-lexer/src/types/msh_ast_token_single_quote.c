/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_single_quote.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 05:35:22 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/18 00:36:20 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/ast/lexer.h>
#include <stdlib.h>

#define TKN_ACTUAL TKN_WORD
#define QUOTE_ALLOC_FAIL ": failed to allocate memory for single \
quote token"
#define UNEXPECTED_EOF "unexpected EOF while looking for matching `''"

static t_ast_error	msh_provide_single_quote(t_ast_lexer *state,
						t_ast_token **tokret, size_t *size)
{
	char		*next;
	char		*value;
	t_ast_error	err;

	next = ft_strchr(state->input + state->cursor + 1, '\'');
	if (next == NULL)
		TRACE(state, TKN_ACTUAL, 2);
	if (next == NULL)
		return (msh_ast_errd(AST_ERROR_UNEXPECTED, UNEXPECTED_EOF,
				true));
	*size = next - (state->input + state->cursor) + 1;
	value = ft_strndup(state->input + state->cursor + 1, *size - 2);
	if (!value)
		TRACE(state, TKN_ACTUAL, 2);
	if (!value)
		return (msh_ast_errd(AST_ERROR_ALLOC, QUOTE_ALLOC_FAIL, false));
	err = msh_ast_token_new(TKN_WORD, tokret);
	if (err.type != AST_ERROR_NONE)
		TRACE(state, TKN_ACTUAL, 2);
	if (err.type != AST_ERROR_NONE)
		free(value);
	(*tokret)->value.string = value;
	return (err);
}

/**
 * It's actually just a really big word ;)
 */
t_ast_error	msh_ast_token_single_quote(t_ast_lexer *state, t_ast_token **token,
				size_t *inc)
{
	t_ast_error	err;
	size_t		size;

	TRACE(state, TKN_ACTUAL, 1);
	err = msh_provide_single_quote(state, token, &size);
	if (err.type != AST_ERROR_NONE)
		return (err);
	*inc = size;
	TRACE(state, TKN_ACTUAL, 0);
	return (err);
}
