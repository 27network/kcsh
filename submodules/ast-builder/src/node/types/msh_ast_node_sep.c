/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_node_sep.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:40:01 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/19 14:03:10 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <msh/ast/builder.h>

static t_list	*msh_list_cutoff(t_list *tokens, t_list *sep)
{
	t_list	*node;

	node = tokens;
	if (node == sep)
		return (NULL);
	while (node && node->next != sep)
		node = node->next;
	if (node->next == sep)
		node->next = NULL;
	else
		return (NULL);
	return (node);
}

t_ast_error	msh_ast_node_sep(t_list *tokens, t_list *sep, t_ast_node **result)
{
	t_ast_node	*node;
	t_ast_error	err;

	node = ft_calloc(1, sizeof(t_ast_node));
	if (!node)
		return (msh_ast_errd(AST_ERROR_ALLOC, "msh_ast_root_node", true));
	node->type = NODE_DELIM;
	err = msh_ast_build(msh_list_cutoff(tokens, sep), &node->left);
	if (err.type != AST_ERROR_NONE)
		msh_ast_node_free(node);
	else
		err = msh_ast_build(sep->next, &node->right);
	if (err.type != AST_ERROR_NONE)
		msh_ast_node_free(node);
	else
		*result = node;
	return (err);
}
