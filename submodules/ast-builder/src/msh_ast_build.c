/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_build.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:17:03 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/18 17:52:58 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/builder.h>

const char	*msh_syntax_error(t_ast_token *token);
t_ast_error	msh_ast_build(t_list *tokens, t_ast_node **result);

static t_list	*msh_ast_find_tkn(t_list *tokens, t_ast_token_type type)
{
	t_list		*node;
	t_list		*last;
	t_ast_token	*tok;

	node = tokens;
	last = NULL;
	while (node)
	{
		tok = (t_ast_token *) node->content;
		if (tok)
		{
			if (tok->type == type)
				last = node;
		}
		node = node->next;
	}
	return (last);
}

static t_list	*msh_list_cutoff(t_list *tokens, t_list *sep)
{
	t_list	*node;
	t_list	*last;

	node = tokens;
	last = NULL;
	while (node && node != sep)
	{
		last = node;
		node = node->next;
	}
	return (last);
}

static t_ast_error	msh_ast_command_node(t_list *tokens, t_ast_node **result)
{
	*result = ft_calloc(1, sizeof(t_ast_node));
	if (!*result)
		return (msh_ast_errd(AST_ERROR_ALLOC, "msh_ast_command_node", true));
	(*result)->type = NODE_COMMAND;
	(*result)->left = NULL;
	(*result)->right = NULL;
	(*result)->data = NULL;
	return (msh_ast_ok());
}

static t_ast_error	msh_ast_root_node(t_list *tokens, t_list *sep,
						t_ast_node **result)
{
	t_ast_error	err;

	if (!sep)
		return (msh_ast_node_command(tokens, result));
	if (!sep->next)
		return (msh_ast_errd(AST_ERROR_UNEXPECTED, "Unexpected end of input",
				true));
	if (sep == tokens)
		return (msh_ast_errd(AST_ERROR_SYNTAX, msh_syntax_error((t_ast_token *)
					sep->content), false));
	*result = ft_calloc(1, sizeof(t_ast_node));
	if (!*result)
		return (msh_ast_errd(AST_ERROR_ALLOC, "msh_ast_root_node", true));
	(*result)->type = NODE_DELIM;
	(*result)->left = NULL;
	(*result)->right = NULL;
	err = msh_ast_build(msh_list_cutoff(tokens, sep), &(*result)->left);
	if (err.code != AST_ERROR_OK)
		msh_ast_node_free(*result);
	else
		err = msh_ast_build(sep->next, &(*result)->right);
	if (err.code != AST_ERROR_OK)
		msh_ast_node_free(*result);
	return (err);
}

t_ast_error	msh_ast_build(t_list *tokens, t_ast_node **result)
{
	t_ast_error	err;
	t_list		*split_node;

	err = msh_ast_ok();
	split_node = msh_ast_find_tkn(tokens, TKN_DELIM);
	if (!split_node)
		split_node = msh_ast_find_tkn(tokens, TKN_PIPE);
	err = msh_ast_root_node(tokens, split_node, result);
	return (err);
}
