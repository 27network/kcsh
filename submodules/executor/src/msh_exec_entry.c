/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_entry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 01:51:43 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/09 03:07:52 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/exec.h>

int	msh_exec(t_exec_state *state, t_ast_node *node)
{
	if (node->type == NODE_COMMAND)
		return (msh_exec_command(state, node));
	if (node->type == NODE_PIPE)
		return (msh_exec_pipe(state, node));
	if (node->type == NODE_DELIM)
		return (msh_exec_delim(state, node));
	return (0);
}

static void	msh_exec_state(t_exec_state *state, t_minishell *msh)
{
	t_ast_node	*node;

	state->msh = msh;
}

int	msh_exec_entry(t_minishell *msh, t_ast_node *node)
{
	t_exec_state	state;

	msh_exec_state(&state, msh);
	return (0);
}
