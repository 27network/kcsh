/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_delim_semicolon.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 22:34:48 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/05 03:54:46 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/exec.h>
#include <msh/util.h>

void	msh_update_env(t_minishell *msh, bool update_lineno);
int		msh_exec_await(t_exec_state *state, int ret, pid_t c_pid);

int	msh_exec_delim_semicolon(t_exec_state *state, t_ast_node *node)
{
	const uint64_t	depth = state->msh->forked;
	int				ret;
	pid_t			c_pid;

	c_pid = 0;
	if (state->msh->flags.debug_executor)
		c_pid = msh_getpid();
	ret = msh_exec(state, (t_ast_node *)node->left);
	if (state->pids)
		ret = msh_exec_await(state, ret, c_pid);
	state->msh->execution_context.exit_code = ret;
	msh_update_env(state->msh, false);
	if (depth == state->msh->forked)
		ret = msh_exec(state, (t_ast_node *)node->right);
	return (ret);
}
