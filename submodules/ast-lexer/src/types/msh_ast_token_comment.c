/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_comment.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 01:43:38 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/30 20:29:05 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/ast/lexer.h>
#include <stdlib.h>

#define TKN_ACTUAL TKN_COMMENT
#define COMMENT_ALLOC_ERR ": failed to allocate memory for comment token"

t_ast_error	msh_ast_token_comment(t_ast_lexer *state, t_ast_token **token,
				size_t *inc)
{
	t_ast_token	*tok;
	t_ast_error	err;
	size_t		len;

	TRACE(state, TKN_ACTUAL, 1);
	len = ft_strcspn(state->input + state->cursor, "\n");
	err = msh_ast_token_new(TKN_COMMENT, &tok);
	if (err.type != AST_ERROR_NONE)
	{
		TRACE(state, TKN_ACTUAL, 2);
		return (err);
	}
	tok->value.string = ft_strndup(state->input + state->cursor, len);
	if (!tok->value.string)
	{
		free(tok);
		TRACE(state, TKN_ACTUAL, 2);
		return (msh_ast_errd(AST_ERROR_ALLOC, COMMENT_ALLOC_ERR, false));
	}
	*inc = len;
	*token = tok;
	TRACE(state, TKN_ACTUAL, 0);
	return (err);
}
