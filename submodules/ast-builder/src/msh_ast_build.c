/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_build.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:17:03 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/19 14:09:18 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
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

static t_ast_error	msh_ast_root_node(t_list *tokens, t_list *sep,
						t_ast_node **result)
{
	if (!sep)
		return (msh_ast_node_command(tokens, result));
	if (!sep->next)
		return (msh_ast_errd(AST_ERROR_UNEXPECTED, "Unexpected end of input",
				true));
	if (sep == tokens)
		return (msh_ast_errd(AST_ERROR_SYNTAX, (void *) msh_syntax_error(
					(t_ast_token *) sep->content), false));
	return (msh_ast_node_sep(tokens, sep, result));
}

t_ast_error	msh_ast_build(t_list *tokens, t_ast_node **result)
{
	t_list		*split_node;

	if (!tokens)
		return (msh_ast_errd(AST_ERROR_ALLOC, "No tokens to parse", false));
	split_node = msh_ast_find_tkn(tokens, TKN_DELIM);
	if (!split_node)
		split_node = msh_ast_find_tkn(tokens, TKN_PIPE);
	return (msh_ast_root_node(tokens, split_node, result));
}
