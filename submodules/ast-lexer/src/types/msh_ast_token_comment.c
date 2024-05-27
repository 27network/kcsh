/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_comment.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 01:43:38 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/27 03:17:50 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/ast/lexer.h>
#include <stdlib.h>

#define COMMENT_ALLOC_ERR ": failed to allocate memory for comment token"

t_ast_error	msh_ast_token_comment(t_ast_lexer *state, t_ast_token **token,
				size_t *inc)
{
	t_ast_token	*tok;
	t_ast_error	err;
	size_t		len;

	len = ft_strcspn(state->input + state->cursor, "\n");
	err = msh_ast_token_new(TKN_COMMENT, &tok);
	if (err.type != AST_ERROR_NONE)
		return (err);
	tok->value.string = ft_strndup(state->input + state->cursor, len);
	if (!tok->value.string)
	{
		free(tok);
		return (msh_ast_errd(AST_ERROR_ALLOC, COMMENT_ALLOC_ERR, false));
	}
	*inc = len;
	*token = tok;
	return (err);
}
