/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_node_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:59:23 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/15 17:56:29 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <msh/ast/builder.h>
#include <stdio.h>

void	msh_ast_node_free_token_tree(t_list *target_list)
{
	ft_lst_delete(target_list, (t_lst_dealloc) msh_ast_token_free);
}

void	msh_ast_node_free(t_ast_node *node)
{
	if (!node)
		return ;
	msh_ast_node_free(node->left);
	msh_ast_node_free(node->right);
	printf("freeing node %p\n", node);
	if (node->tree_tokens)
		printf("freeing tree tokens %p\n", node->tree_tokens);
	if (node->tree_tokens)
		ft_lst_free(&node->tree_tokens,
			(t_lst_dealloc) msh_ast_node_free_token_tree);
	printf("freed node %p\n", node);
	free(node);
}
