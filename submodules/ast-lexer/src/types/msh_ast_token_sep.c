/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_sep.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:25:04 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/27 02:50:17 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/ast/lexer.h>
#include <stdlib.h>

#define SEPARATOR_ALLOC_FAIL ": failed to allocate memory for separator token"

static size_t	msh_find_sep_string(const char *input)
{
	size_t	i;

	i = 0;
	while (input[i] && ft_strchr(SEP_CHARS, input[i]) != NULL)
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

	len = msh_find_sep_string(state->input + state->cursor);
	sep = ft_strndup(state->input + state->cursor, len);
	if (!sep)
		return (msh_ast_errd(AST_ERROR_ALLOC, SEPARATOR_ALLOC_FAIL, false));
	err = msh_ast_token_new(TKN_SEP, &tok);
	if (err.type != AST_ERROR_NONE)
	{
		free(sep);
		return (err);
	}
	tok->value.string = sep;
	*inc = len;
	*token = tok;
	return (err);
}
