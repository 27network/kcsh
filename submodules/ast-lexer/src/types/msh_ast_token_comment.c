/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_comment.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 01:43:38 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/18 13:22:53 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/ast/lexer.h>
#include <stdlib.h>

#define TKN_ACTUAL TKN_COMMENT

t_ast_error	msh_ast_token_comment(t_ast_lexer *state, t_ast_token **token,
				size_t *inc)
{
	size_t		len;

	TRACE(state, TKN_ACTUAL, 1);
	len = ft_strcspn(state->input + state->cursor, "\n");
	*inc = len;
	*token = NULL;
	TRACE(state, TKN_ACTUAL, 0);
	return (msh_ast_ok());
}
