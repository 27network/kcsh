/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_node_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:59:23 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/15 23:25:43 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <msh/ast/builder.h>
#include <stdio.h>

void	msh_ast_node_free_token_tree(t_list *target_list)
{
	printf(">>>> Tree token freeing %p\n", target_list); fflush(stdout);
	ft_lst_delete(target_list, (t_lst_dealloc) msh_ast_token_free);
	printf(">>>> DONE freeing tree token %p\n", target_list); fflush(stdout);
}

void	msh_ast_node_free(t_ast_node *node)
{
	if (!node)
		return ;
	printf("----- freeing node %p\n", node); fflush(stdout);
	msh_ast_node_free(node->left);
	msh_ast_node_free(node->right);
	printf("------ freeing tree token %p\n", node->tree_tokens); fflush(stdout);
	if (node->tree_tokens)
		ft_lst_free(&node->tree_tokens,
			(t_lst_dealloc) msh_ast_node_free_token_tree);
	if (node->command.tokens)
		ft_lst_free(&node->command.tokens,
			(t_lst_dealloc) msh_ast_token_free);
	free(node);
	printf("------ DONE FREEING NODE %p\n", node); fflush(stdout);
}
