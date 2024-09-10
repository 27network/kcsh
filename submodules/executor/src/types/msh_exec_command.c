/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 01:51:37 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/09 03:06:31 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/exec.h>
#include <msh/log.h>
#include <stdio.h>
#include <unistd.h>

int	msh_exec_command_infork(t_exec_state *state, t_ast_node *node)
{

}

int	msh_exec_command_outfork(t_exec_state *state, const char **cmdline)
{
}

int	msh_exec_command_prepare(t_exec_state *state, const char **cmdline)
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
		perror("fork");
		return (1);
	}
	if (pid == 0)
		return (msh_exec_command_infork(state, cmdline));
	return (msh_exec_command_outfork(state, node));
}

int	msh_exec_command(t_exec_state *state, t_ast_node *node)
{
	if (!msh_ast_expand(state->msh, node))
	{
		msh_error(state->msh, "expansion error\n");
		return (1);
	}
	return (0);
}
