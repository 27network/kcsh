/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_entry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 01:51:43 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/30 08:58:26 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <ft/mem.h>
#include <msh/ast/builder.h>
#include <msh/exec.h>
#include <msh/log.h>
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

int	msh_exec_entry(t_minishell *msh, t_ast_node *node)
{
	t_exec_state	state;
	int				ret;
	bool			ret_found;
	int				s;
	pid_t			pid;

	msh_exec_state(&state, msh);
	ret = msh_exec(&state, node);
	ret_found = ret != 0;
	while (state.pids)
	{
		pid = (pid_t)(uint64_t)state.pids->content;
		ft_lst_remove(&state.pids, state.pids, NULL);
		msh_log(msh, MSG_DEBUG_EXECUTOR, "Waiting for pid %d\n", pid);
		if (waitpid(pid, &s, 0) == -1 && (errno != EINTR && errno != ECHILD))
			msh_error(msh, "failed to wait for pid %d (entry): %m\n", pid);
		else if (!ret_found)
			ret = msh_exec_status(s);
		else
			(void)msh_exec_status(s);
		ret_found = true;
	}
	msh->execution_context.exit_code = ret;
	msh_log(msh, MSG_DEBUG_EXECUTOR, "Done executing AST node %p\n", node);
	return (0);
}
