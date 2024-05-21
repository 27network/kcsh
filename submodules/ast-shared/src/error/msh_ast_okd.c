/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_okd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:48:23 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/21 13:48:34 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/error.h>

t_ast_error	msh_ast_okd(void *data)
{
	return ((t_ast_error){.type = AST_ERROR_NONE, .data = data});
}
