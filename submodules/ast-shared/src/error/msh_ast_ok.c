/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_ok.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:47:39 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/26 21:49:08 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/error.h>

t_ast_error	msh_ast_ok(void)
{
	return ((t_ast_error){
		.type = AST_ERROR_NONE,
		.data = NULL,
		.retry = false
	});
}
