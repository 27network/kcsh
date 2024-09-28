/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_sep.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:25:04 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/28 13:54:40 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/ast/lexer.h>
#include <stdlib.h>

#define TKN_ACTUAL TKN_SEP
#define SEP_CHARS_ACTUAL " \t"
#define SEPARATOR_ALLOC_FAIL ": failed to allocate memory for separator token"

static int	msh_token_type(t_ast_lexer *state)
{
	const bool	inside_string = msh_ast_lexer_is_delim(state, '"');
	const bool	inside_word = msh_ast_lexer_is_delim(state, '\'');

	if (inside_string || inside_word)
		return (TKN_WORD);
	return (TKN_SEP);
}

static size_t	msh_find_sep_string(const char *input)
{
	size_t	i;

	i = 0;
	while (input[i] && ft_strchr(SEP_CHARS_ACTUAL, input[i]) != NULL)
		i++;
	return (i);
}

t_ast_error	msh_ast_token_sep(t_ast_lexer *state, t_ast_token **token,
				size_t *inc)
{
	t_ast_token	*tok;
	t_ast_error	err;
	char		*sep;
	size_t		len;

	TRACE(state, TKN_ACTUAL, 1);
	len = msh_find_sep_string(state->input + state->cursor);
	sep = ft_strndup(state->input + state->cursor, len);
	if (!sep)
	{
		TRACE(state, TKN_ACTUAL, 2);
		return (msh_ast_errd(AST_ERROR_ALLOC, SEPARATOR_ALLOC_FAIL, false));
	}
	err = msh_ast_token_new(msh_token_type(state), &tok);
	if (err.type != AST_ERROR_NONE)
	{
		TRACE(state, TKN_ACTUAL, 2);
		free(sep);
		return (err);
	}
	tok->value.string = sep;
	*inc = len;
	*token = tok;
	TRACE(state, TKN_ACTUAL, 0);
	return (err);
}
