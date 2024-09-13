/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 01:51:37 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/13 19:04:00 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/data/list.h>
#include <msh/exec.h>
#include <msh/log.h>
#include <stdio.h>
#include <unistd.h>

static void	msh_exec_command_stdin(t_exec_state *state, t_list *fd_node)
{
	const int	*fd = (int *)fd_node->content;

	dup2(*fd, 0);
	close(*fd);
	(void) state;
}

static int	msh_exec_command_infork(
	t_exec_state *state,
	const char **cmdline,
	int fds[2]
) {
	if (state->fd_stack)
		msh_exec_command_stdin(state, ft_lst_last(state->fd_stack));
	close(fds[0]);
	dup2(fds[1], 1);
	close(fds[1]);
	(void) cmdline;
	//TODO: redirections
	return (0);
}

static int	msh_exec_command_outfork(
	t_exec_state *state,
	const char **cmdline,
	int fds[2]
) {
	close(fds[1]);
	(void) cmdline;
	(void) state;
	// msh_exec_push_fd(state, fds[0], 0);
	return (0);
}

[[maybe_unused]]
static int	msh_exec_command_prepare(t_exec_state *state, const char **cmdline)
{
	pid_t	pid;
	int		fds[2];

	if (pipe(fds) == -1)
	{
		perror("pipe");
		return (1);
	}
	pid = msh_fork(state->msh);
	if (pid == -1)
	{
		close(fds[0]);
		close(fds[1]);
		perror("fork");
		return (1);
	}
	if (pid == 0)
		return (msh_exec_command_infork(state, cmdline, fds));
	return (msh_exec_command_outfork(state, cmdline, fds));
}

//TODO: transform
//TODO: expansions
//TODO: check redirs
//TODO: check builtin <------
//TODO: exec
int	msh_exec_command(t_exec_state *state, t_ast_node *node)
{
	t_ast_error	err;

	err = msh_ast_transform(state->msh, &node->tokens);
	printf("msh_exec_command\n");
	printf("node->type: %s\n", msh_ast_node_strtype(node->type));
	return (0);
}
