/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_node_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:59:23 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/19 13:59:32 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <msh/ast/builder.h>

void	msh_ast_node_free(t_ast_node *node)
{
	if (!node)
		return ;
	msh_ast_node_free(node->left);
	msh_ast_node_free(node->right);
	free(node);
}
