/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_node_group.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:17:28 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/05 04:31:00 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <msh/ast/builder.h>
#include <msh/log.h>

void	msh_dump_tokens(t_minishell *msh, t_list *tokens);

static t_ast_error	msh_ast_node_group_children(t_minishell *msh,
						t_list *tokens, t_ast_node **result)
{
	t_ast_error	err;

	err = msh_ast_build(msh, tokens, &(*result)->left);
	if (err.type != AST_ERROR_NONE)
	{
		msh_ast_node_free(*result);
		*result = NULL;
	}
	else
		(*result)->left->parent = *result;
	return (err);
}

t_ast_error	msh_ast_node_group(t_minishell *msh, t_list *tokens,
				t_ast_node **result)
{
	t_ast_error	error;
	t_list		*node;
	t_ast_token	*tok;

	node = tokens;
	while (node && (((t_ast_token *)node->content)->type != TKN_GROUP))
		node = node->next;
	if (!node)
		return (msh_ast_errd(AST_ERROR_ALLOC, "msh_ast_node_group", false));
	error = msh_ast_node_new(result, NODE_GROUP);
	if (error.type)
		return (error);
	msh_log(msh, MSG_DEBUG_AST_BUILDER, "building group node\n");
	if (msh->flags.debug_ast)
		msh_dump_tokens(msh, tokens);
	(*result)->group.tokens = tokens;
	(*result)->group.group = node;
	tok = (t_ast_token *)node->content;
	return (msh_ast_node_group_children(msh, tok->value.list, result));
}
