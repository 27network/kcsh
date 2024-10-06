/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_entry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 01:51:43 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/05 03:55:27 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <ft/mem.h>
#include <msh/ast/builder.h>
#include <msh/exec.h>
#include <msh/log.h>
#include <msh/signal.h>
#include <msh/util.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int	msh_exec(t_exec_state *state, t_ast_node *node)
{
	int		ret;

	ret = -1;
	state->depth++;
	msh_log(state->msh, MSG_DEBUG_EXECUTOR, "Executing AST node %p (%s) at de"
		"pth %d\n", node, msh_ast_node_strtype(node->type), (int)state->depth);
	if (state->msh->execution_context.interrupt)
		return (128 + SIGINT);
	if (node->type == NODE_COMMAND)
		ret = msh_exec_command(state, node);
	if (node->type == NODE_PIPE)
		ret = msh_exec_pipe(state, node);
	if (node->type == NODE_DELIM)
		ret = msh_exec_delim(state, node);
	if (node->type == NODE_GROUP)
		ret = msh_exec_group(state, node);
	state->depth--;
	return (ret);
}

static void	msh_exec_state(t_exec_state *state, t_minishell *msh)
{
	ft_bzero(state, sizeof(t_exec_state));
	state->msh = msh;
}

int	msh_exec_await(t_exec_state *state, int ret, pid_t c_pid)
{
	const bool	interactive = state->msh->interactive;
	int			s;
	pid_t		pid;

	state->msh->interactive = false;
	msh_signal_init(state->msh, false);
	while (state->pids)
	{
		s = 0;
		pid = (pid_t)(uint64_t)state->pids->content;
		ft_lst_remove(&state->pids, state->pids, NULL);
		if (state->msh->forked)
			continue ;
		msh_log(state->msh, MSG_DEBUG_EXECUTOR, "[%d] wait(%d)\n", c_pid, pid);
		if (waitpid(pid, &s, 0) == -1 && (errno != EINTR && errno != ECHILD))
			msh_error(state->msh, "failed to wait for pid %d (entry): %m\n",
				pid);
		else
			ret = msh_exec_status_impl(state->msh, s, false);
	}
	state->msh->interactive = interactive;
	msh_signal_init(state->msh, false);
	return (ret);
}

void	msh_update_env(t_minishell *msh, bool update_lineno);

int	msh_exec_entry(t_minishell *msh, t_ast_node *node)
{
	t_exec_state	state;
	int				ret;
	pid_t			c_pid;

	msh->execution_context.interrupt = false;
	msh_exec_state(&state, msh);
	ret = msh_exec(&state, node);
	c_pid = 0;
	if (msh->flags.debug_executor)
		c_pid = msh_getpid();
	if (state.pids)
		ret = msh_exec_await(&state, ret, c_pid);
	msh->execution_context.exit_code = ret;
	msh_update_env(msh, false);
	msh_log(msh, MSG_DEBUG_EXECUTOR, "Done executing AST node %p\n", node);
	msh->execution_context.interrupt = false;
	return (0);
}
