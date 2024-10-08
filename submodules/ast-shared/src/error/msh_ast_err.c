/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:48:42 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/25 07:41:24 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/error.h>

t_ast_error	msh_ast_err(t_ast_error_type type, bool retry)
{
	return ((t_ast_error){.type = type, .data = NULL, .retry = retry});
}
