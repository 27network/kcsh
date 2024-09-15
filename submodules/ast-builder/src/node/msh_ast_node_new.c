/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_node_new.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:36:13 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/15 18:28:10 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <msh/ast/builder.h>

#define ERROR_MESSAGE "Failed to allocate memory for node"

t_ast_error	msh_ast_node_new_filled(t_ast_node **result, t_ast_node_type type,
				t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*node;

	*result = NULL;
	node = ft_calloc(1, sizeof(t_ast_node));
	if (!node)
		return (msh_ast_errd(AST_ERROR_ALLOC, ERROR_MESSAGE, false));
	node->type = type;
	node->left = left;
	node->right = right;
	*result = node;
	return (msh_ast_ok());
}

t_ast_error	msh_ast_node_new(t_ast_node **result, t_ast_node_type type)
{
	return (msh_ast_node_new_filled(result, type, NULL, NULL));
}

t_ast_error	msh_ast_node_new_child(t_ast_node **result, t_ast_node_type type,
				t_ast_node *parent)
{
	t_ast_node	*node;
	t_ast_error	error;

	*result = NULL;
	error = msh_ast_node_new(&node, type);
	if (error.type)
		return (error);
	node->parent = parent;
	*result = node;
	return (msh_ast_ok());
}
