/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:08:14 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/18 16:54:06 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/builder.h>
#include <msh/log.h>

#define PRE "DOT|	"
#define LOGTYPE MSG_DEBUG_AST_BUILDER

static void	msh_ast_print_decls(t_ast_node *node, int depth, int id)
{
	if (!node)
		return ;
	if (depth == 0)
		return ;
	msh_log(msh, LOGTYPE, PRE"node%d[label=\"<f0> |<f1> %s (%s)\n |<f2>\"];\n",
		id, msh_ast_strtype(node->type), "");
	msh_ast_print_decls(node->left, depth - 1, id * 2 + 1);
	msh_ast_print_decls(node->right, depth - 1, id * 2 + 2);
}

static void	msh_ast_print_connects(t_ast_node *node, int depth, int id)
{
	if (!node)
		return ;
	if (depth == 0)
		return ;
	if (node->left)
		msh_log(msh, LOGTYPE, PRE"\"node%d\":f0 -> \"node%d\":f1;\n",
			id, id * 2 + 1);
	if (node->right)
		msh_log(msh, LOGTYPE, PRE"\"node%d\":f2 -> \"node%d\":f1;\n",
			id, id * 2 + 2);
	msh_ast_print_connects(node->left, depth - 1, id * 2 + 1);
	msh_ast_print_connects(node->right, depth - 1, id * 2 + 2);
}

#define PRE "DOT|"

void	msh_ast_print(t_minishell *msh, t_ast_node *node, int depth)
{
	msh_log(msh, LOGTYPE, PRE"digraph AST {\n");
	msh_log(msh, LOGTYPE, PRE"	node [shape=record,height=.2];\n");
	msh_ast_print_decl(node, depth, 0);
	msh_ast_print_connects(node, depth, 0);
	msh_log(msh, LOGTYPE, PRE"}\n");
}
