/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_simple.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 08:27:16 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/27 00:45:39 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <msh/ast/lexer.h>

#define TOKEN_ALLOC_ERR ": failed to allocate memory for token"

t_ast_error	msh_ast_token_simple(t_ast_token_type type, t_ast_token **tknret,
				size_t *inc, size_t size)
{
	t_ast_token	*token;

	token = ft_calloc(1, sizeof(t_ast_token));
	if (!token)
	{
		*tknret = NULL;
		return (msh_ast_errd(AST_ERROR_ALLOC, TOKEN_ALLOC_ERR, false));
	}
	token->type = type;
	*tknret = token;
	*inc = size;
	return (msh_ast_ok());
}
