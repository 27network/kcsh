/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_errd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:48:58 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/21 13:49:01 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/error.h>

t_ast_error	msh_ast_errd(t_ast_error_type type, void *data)
{
	return ((t_ast_error){.type = type, .data = data});
}
