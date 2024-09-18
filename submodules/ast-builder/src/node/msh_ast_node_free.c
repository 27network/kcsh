/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_node_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:59:23 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/18 17:12:04 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <msh/ast/builder.h>
#include <stdio.h>

void	msh_ast_node_free_token_tree(t_list *target_list)
{
	t_ast_token	*token;

	if (target_list->content)
	{
		token = (t_ast_token *) target_list->content;
		if (token->value.list && (token->type == TKN_GROUP
				|| token->type == TKN_STRING))
			token->value.list = NULL;
	}
	ft_lst_delete(target_list, (t_lst_dealloc) msh_ast_token_free);
}

void	msh_ast_node_free(t_ast_node *node)
{
	if (!node)
		return ;
	msh_ast_node_free(node->left);
	msh_ast_node_free(node->right);
	if (node->tree_tokens)
		ft_lst_free(&node->tree_tokens,
			(t_lst_dealloc) msh_ast_node_free_token_tree);
	free(node);
}
