/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 03:07:59 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/30 08:14:23 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <msh/exec.h>
#include <msh/log.h>
#include <stdint.h>
# include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

// static inline int	msh_exec_pipe_run(t_exec_state *state, t_ast_node *node,
// 						int fds[2])
// {
// 	const t_ast_node	*left = node->left;
// 	const t_ast_node	*right = node->right;
// 	const bool			pipe_state = state->is_in_pipe;
// 	int					ret;
//
// 	state->is_in_pipe = true;
// 	ret = msh_exec(state, (t_ast_node *)left);
// 	if (ret != 0 || state->msh->forked)
// 	{
// 		close(fds[0]);
// 		return (ret);
// 	}
// 	ret = msh_exec(state, (t_ast_node *)right);
// 	state->is_in_pipe = pipe_state;
// 	return (ret);
// }

static inline int	msh_exec_pipe_left(t_exec_state *state, t_ast_node *node,
						int fds[2])
{
	pid_t	pid;
	int		status;

	pid = msh_fork(state->msh);
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		close(fds[0]);
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			return (1);
		close(fds[1]);
		return (msh_exec(state, (t_ast_node *)node->left));
	}
	close(fds[1]);
	if (!ft_lst_tadd(&state->pids, (void *)(uint64_t)pid))
	{
		msh_error(state->msh, "failed to push pid %d, awaiting\n", pid);
		waitpid(pid, &status, 0);
		msh_exec_status(status);
		return (1);
	}
	return (0);
}

static inline int	msh_exec_pipe_right(t_exec_state *state, t_ast_node *node,
						int fds[2])
{
	pid_t	pid;
	int		status;

	pid = msh_fork(state->msh);
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		if (dup2(fds[0], STDIN_FILENO) == -1)
			return (1);
		close(fds[0]);
		return (msh_exec(state, (t_ast_node *)node->right));
	}
	close(fds[0]);
	if (!ft_lst_tadd(&state->pids, (void *)(uint64_t)pid))
	{
		msh_error(state->msh, "failed to push pid %d, awaiting\n", pid);
		waitpid(pid, &status, 0);
		msh_exec_status(status);
		return (1);
	}
	return (0);
}

int	msh_exec_pipe(t_exec_state *state, t_ast_node *node)
{
	const uint64_t		depth = state->msh->forked;
	int					fds[2];
	int					ret;
	const bool			interactive = state->msh->interactive;

	if (!node->left || !node->right)
		return (1);
	ft_bzero(fds, sizeof(fds));
	if (pipe(fds) == -1)
		return (1);
	state->msh->interactive = false;
	ret = msh_exec_pipe_left(state, node, fds);
	state->msh->interactive = interactive;
	if (ret != 0 || state->msh->forked != depth)
		return (ret);
	state->msh->interactive = false;
	ret = msh_exec_pipe_right(state, node, fds);
	state->msh->interactive = interactive;
	return (ret);
}
