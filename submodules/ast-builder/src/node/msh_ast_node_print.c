/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_node_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:08:14 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/06 18:42:31 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/print.h>
#include <ft/string.h>
#include <msh/ast/builder.h>
#include <msh/log.h>

#define PRE "DOT|"
#define LOGTYPE MSG_DEBUG_AST_BUILDER
#define CHAR_OR "│" // a special unicode character to prevent graphwiz from 
					// fucking up the display

const char	*msh_ast_strdelim(t_ast_delim_type type);

static const char	*msh_depth_str(int depth)
{
	static char	*str = NULL;
	static int	last_depth = 0;
	size_t		len;

	if (depth == last_depth)
		return (str);
	if (str)
		ft_strdel(&str);
	if (depth == -1)
		return (str);
	str = ft_calloc(sizeof(char), depth + 1);
	if (!str)
		return (str);
	len = 0;
	while (len < (size_t) depth)
		str[len++] = '\t';
	str[len] = '\0';
	last_depth = depth;
	return (str);
}

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
				int id, int depth)
{
	char	*left;
	char	*right;

	if (!node)
		return ;
	if (node->type == NODE_GROUP)
	{
		msh_log(msh, LOGTYPE, PRE"%ssubgraph cluster%d {\n",
			msh_depth_str(depth++), id);
		msh_ast_print_decls(msh, node->left, id, depth);
		msh_log(msh, LOGTYPE, PRE"%s}\n", msh_depth_str(depth - 1));
	}
	else
	{
		left = "";
		if (node->left)
			left = "<f0> |";
		right = "";
		if (node->right)
			right = " | <f2>";
		msh_log(msh, LOGTYPE, PRE"%snode%d[label=\"%s<f1> %s%s\"];\n",
			msh_depth_str(depth), id, left, msh_ast_stringify(node), right);
		msh_ast_print_decls(msh, node->left, id * 2 + 1, depth);
		msh_ast_print_decls(msh, node->right, id * 2 + 2, depth);
	}
}

static void	msh_ast_print_connects(t_minishell *msh, t_ast_node *node,
				int id, int depth)
{
	if (!node)
		return ;
	if (node->type == NODE_GROUP)
		msh_ast_print_connects(msh, node->left, id, depth);
	else
	{
		if (node->left)
			msh_log(msh, LOGTYPE, PRE"%s\"node%d\":f0 -> \"node%d\":f1;\n",
				msh_depth_str(depth), id, id * 2 + 1);
		if (node->right)
			msh_log(msh, LOGTYPE, PRE"%s\"node%d\":f2 -> \"node%d\":f1;\n",
				msh_depth_str(depth), id, id * 2 + 2);
		msh_ast_print_connects(msh, node->left, id * 2 + 1, depth);
		msh_ast_print_connects(msh, node->right, id * 2 + 2, depth);
	}
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
	msh_ast_print_decls(msh, node, 0, 1);
	msh_ast_print_connects(msh, node, 0, 1);
	msh_log(msh, LOGTYPE, PRE"}\n");
	msh_depth_str(-1);
}
