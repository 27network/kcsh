/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_node_sep.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:40:01 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/19 05:54:25 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <msh/ast/builder.h>
#include <msh/log.h>

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
	return (tokens);
}

// tmp -> start of list (left side)
// sep -> sep token
// target sep#next -> start of list (right side)
static t_ast_error	msh_ast_node_sep_children(t_minishell *msh, t_list *tmp,
						t_ast_node *node, t_list *sep)
{
	t_ast_error	err;

	err = msh_ast_build(msh, tmp, &node->left);
	if (err.type != AST_ERROR_NONE)
		msh_ast_node_free(node);
	else
		err = msh_ast_build(msh, sep->next, &node->right);
	if (err.type != AST_ERROR_NONE)
		msh_ast_node_free(node);
	return (err);
}

t_ast_error	msh_ast_node_sep(t_minishell *msh, t_list *tokens, t_list *sep,
				t_ast_node **result)
{
	t_ast_node	*node;
	t_ast_error	err;
	t_list		*tmp;

	node = ft_calloc(1, sizeof(t_ast_node));
	if (!node)
		return (msh_ast_errd(AST_ERROR_ALLOC, "msh_ast_root_node", true));
	node->type = NODE_PIPE;
	if (((t_ast_token *) sep->content)->type == TKN_DELIM)
		node->type = NODE_DELIM;
	if (node->type == NODE_DELIM)
		node->delim = ((t_ast_token *) sep->content)->kind;
	msh_log(msh, MSG_DEBUG_AST_BUILDER, "building sep node (%s)\n",
		msh_ast_node_strtype(node->type));
	tmp = msh_list_cutoff(tokens, sep);
	if (!tmp)
		return (msh_ast_errd(AST_ERROR_ALLOC, "msh_ast_node_sep", true));
	err = msh_ast_node_sep_children(msh, tmp, node, sep);
	if (tmp && err.type != AST_ERROR_NONE)
		ft_lst_last(tmp)->next = sep;
	msh_log(msh, MSG_DEBUG_AST_BUILDER, "current node: %p, child: %p %p\n",
		node, node->left, node->right);
	*result = node;
	return (err);
}
