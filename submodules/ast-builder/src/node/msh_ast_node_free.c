/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_node_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:59:23 by kiroussa          #+#    #+#             */
/*   Updated: 2024/08/26 13:51:34 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <msh/ast/builder.h>

static void	msh_ast_free_command(t_ast_node *node)
{
	ft_lst_free(&node->command.tokens, (t_lst_dealloc) msh_ast_token_free);
	ft_lst_free(&node->command.env, (t_lst_dealloc) msh_ast_token_free);
	ft_lst_free(&node->command.args, (t_lst_dealloc) msh_ast_token_free);
	ft_lst_free(&node->command.redirs, (t_lst_dealloc) msh_ast_token_free);
	// ft_lst_free(&node->command.heredocs, (t_lst_dealloc) msh_ast_token_free);
}

void	msh_ast_node_free(t_ast_node *node)
{
	if (!node)
		return ;
	msh_ast_node_free(node->left);
	msh_ast_node_free(node->right);
	if (node->type == NODE_COMMAND)
		msh_ast_free_command(node);
	free(node);
}
