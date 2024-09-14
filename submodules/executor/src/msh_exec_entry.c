/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_entry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 01:51:43 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/14 18:34:01 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <msh/ast/builder.h>
#include <msh/exec.h>
#include <msh/log.h>

int	msh_exec(t_exec_state *state, t_ast_node *node)
{
	if (node->type == NODE_COMMAND)
		return (msh_exec_command(state, node));
	if (node->type == NODE_PIPE)
		return (msh_exec_pipe(state, node));
	if (node->type == NODE_DELIM)
		return (msh_exec_delim(state, node));
	msh_error(state->msh, "Unknown AST node type: %s",
		msh_ast_node_strtype(node->type));
	return (1);
}

static void	msh_exec_state(t_exec_state *state, t_minishell *msh)
{
	ft_bzero(state, sizeof(t_exec_state));
	state->msh = msh;
}

int	msh_exec_entry(t_minishell *msh, t_ast_node *node)
{
	t_exec_state	state;
	int				ret;

	msh_exec_state(&state, msh);
	msh_log(msh, MSG_DEBUG_EXECUTOR, "Executing AST node %p\n", node);
	ret = msh_exec(&state, node);
	return (ret);
}
