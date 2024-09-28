/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_entry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 01:51:43 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/28 19:49:31 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <msh/ast/builder.h>
#include <msh/exec.h>
#include <msh/log.h>

int	msh_exec(t_exec_state *state, t_ast_node *node)
{
	int		ret;
	bool	is_in_pipe;

	if (node->type == NODE_COMMAND)
		ret = msh_exec_command(state, node);
	if (node->type == NODE_PIPE)
	{
		is_in_pipe = state->is_in_pipe;
		state->is_in_pipe = true;
		ret = msh_exec_pipe(state, node);
		state->is_in_pipe = is_in_pipe;
	}
	if (node->type == NODE_DELIM)
		ret = msh_exec_delim(state, node);
	return (ret);
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
