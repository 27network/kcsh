/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_node_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:31:21 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/19 13:57:54 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <msh/ast/builder.h>

t_ast_error	msh_ast_node_command(t_list *tokens, t_ast_node **result)
{
	(void) tokens;
	*result = NULL;
	return (msh_ast_ok());
}
