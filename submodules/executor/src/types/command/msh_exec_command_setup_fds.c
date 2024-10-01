/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_command_setup_fds.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 19:31:40 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/01 12:27:01 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/data/list.h>
#include <msh/exec.h>
#include <msh/log.h>
#include <unistd.h>

int	msh_save_fds(t_minishell *msh, int fds[3])
{
	int		ret;

	(void) msh;
	ret = dup(STDIN_FILENO);
	if (ret == -1)
		return (0);
	fds[STDIN_FILENO] = ret;
	ret = dup(STDOUT_FILENO);
	if (ret == -1)
	{
		close(fds[STDIN_FILENO]);
		return (0);
	}
	fds[STDOUT_FILENO] = ret;
	ret = dup(STDERR_FILENO);
	if (ret == -1)
	{
		close(fds[STDIN_FILENO]);
		close(fds[STDOUT_FILENO]);
		return (0);
	}
	fds[STDERR_FILENO] = ret;
	return (1);
}

int	msh_restore_fds(t_minishell *msh, int fds[3])
{
	int		ret;

	(void) msh;
	ret = dup2(fds[STDIN_FILENO], STDIN_FILENO);
	close(fds[STDIN_FILENO]);
	if (ret == -1)
	{
		close(fds[STDOUT_FILENO]);
		close(fds[STDERR_FILENO]);
		return (0);
	}
	ret = dup2(fds[STDOUT_FILENO], STDOUT_FILENO);
	close(fds[STDOUT_FILENO]);
	if (ret == -1)
	{
		close(fds[STDERR_FILENO]);
		return (0);
	}
	ret = dup2(fds[STDERR_FILENO], STDERR_FILENO);
	close(fds[STDERR_FILENO]);
	return (ret != -1);
}
