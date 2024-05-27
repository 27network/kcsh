/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_new.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 10:03:20 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/27 00:46:10 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <msh/ast/lexer.h>

t_ast_error	msh_ast_token_new(t_ast_token_type type, t_ast_token **tknret)
{
	t_ast_token	*token;

	token = ft_calloc(1, sizeof(t_ast_token));
	if (!token)
		*tknret = NULL;
	if (!token)
		return (msh_ast_err(AST_ERROR_ALLOC, false));
	token->type = type;
	token->value.data = NULL;
	token->kind = -1;
	*tknret = token;
	return (msh_ast_ok());
}
