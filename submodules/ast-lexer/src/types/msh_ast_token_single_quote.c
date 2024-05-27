/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_single_quote.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 05:35:22 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/27 05:40:24 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/ast/lexer.h>
#include <stdlib.h>

#define SINGLE_QUOTE_ALLOC_FAIL ": failed to allocate memory for single \
quote token"

/**
 * It's actually just a really big word ;)
 */
t_ast_error	msh_ast_token_single_quote(t_ast_lexer *state, t_ast_token **token,
				size_t *inc)
{
	t_ast_error	err;
	char		*next;
	size_t		size;
	char		*value;

	next = ft_strchr(state->input + state->cursor + 1, '\'');
	if (next == NULL)
		return (msh_ast_errd(AST_ERROR_UNEXPECTED, "unexpected end of input",
				true));
	size = next - (state->input + state->cursor) + 1;
	value = ft_strndup(state->input + state->cursor, size);
	if (!value)
		return (msh_ast_errd(AST_ERROR_ALLOC, SINGLE_QUOTE_ALLOC_FAIL,
				false));
	err = msh_ast_token_new(TKN_WORD, token);
	if (err.type != AST_ERROR_NONE)
		free(value);
	if (err.type != AST_ERROR_NONE)
		return (err);
	(*token)->value.string = value;
	*inc = size;
	return (err);
}
