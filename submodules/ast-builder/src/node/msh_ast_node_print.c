/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_node_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:08:14 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/08 16:20:35 by emfriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <msh/ast/builder.h>
#include <msh/log.h>

#define PRE "DOT|	"
#define LOGTYPE MSG_DEBUG_AST_BUILDER
#define CHAR_OR "│" // a special unicode character to prevent graphwiz from 
					// fucking up the display

const char	*msh_ast_strdelim(t_ast_delim_type type);

static const char	*msh_ast_stringify(t_ast_node *node)
{
	const t_ast_node_type	type = node->type;
	t_ast_token				*first_word;
	t_list					*tmp;

	if (type == NODE_COMMAND)
	{
		tmp = node->command.tokens;
		if (!tmp)
			return ("empty");
		while (tmp->next && ((t_ast_token *) tmp->content)->type == TKN_SEP)
			tmp = tmp->next;
		first_word = (t_ast_token *) tmp->content;
		if (first_word->type == TKN_WORD)
			return (first_word->value.string);
		return (msh_ast_strtoken(first_word->type));
	}
	if (type == NODE_DELIM && node->delim == DELIM_OR)
		return (CHAR_OR CHAR_OR);
	if (type == NODE_DELIM)
		return (msh_ast_strdelim(node->delim));
	if (type == NODE_PIPE)
		return (CHAR_OR);
	return (msh_ast_node_strtype(type));
}

static void	msh_ast_print_decls(t_minishell *msh, t_ast_node *node,
				int id)
{
	if (!node)
		return ;
	msh_log(msh, LOGTYPE, PRE"node%d[label=\"<f0> |<f1> %s |<f2>\"];\n",
		id, msh_ast_stringify(node));
	msh_ast_print_decls(msh, node->left, id * 2 + 1);
	msh_ast_print_decls(msh, node->right, id * 2 + 2);
}

static void	msh_ast_print_connects(t_minishell *msh, t_ast_node *node,
				int id)
{
	if (!node)
		return ;
	if (node->left)
		msh_log(msh, LOGTYPE, PRE"\"node%d\":f0 -> \"node%d\":f1;\n",
			id, id * 2 + 1);
	if (node->right)
		msh_log(msh, LOGTYPE, PRE"\"node%d\":f2 -> \"node%d\":f1;\n",
			id, id * 2 + 2);
	msh_ast_print_connects(msh, node->left, id * 2 + 1);
	msh_ast_print_connects(msh, node->right, id * 2 + 2);
}

#undef PRE
#define PRE "DOT|"

void	msh_ast_node_print(t_minishell *msh, t_ast_node *node)
{
	if (!msh->flags.debug_ast)
		return ;
	ft_printf("\n");
	msh_log(msh, LOGTYPE, PRE"digraph AST {\n");
	msh_log(msh, LOGTYPE, PRE"	node [shape=record,height=.2];\n");
	msh_ast_print_decls(msh, node, 0);
	msh_ast_print_connects(msh, node, 0);
	msh_log(msh, LOGTYPE, PRE"}\n");
}
