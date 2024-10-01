/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:21:50 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/01 12:51:02 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <msh/signal.h>
#include <sys/wait.h>

#ifndef WCOREDUMP

bool	_wcoredump(int status)
{
	return (status & 0x80);
}

# define WCOREDUMP _wcoredump
#endif

int	msh_exec_status_impl(int wait_status, bool in_pipe)
{
	int	sig;

	if (WIFSIGNALED(wait_status))
	{
		sig = WTERMSIG(wait_status);
		if (sig != SIGINT && sig != SIGTERM && sig != SIGPIPE)
		{
			ft_dprintf(2, "%s", msh_strsignal(sig));
			if (WCOREDUMP(wait_status))
				ft_dprintf(2, " (core dumped)");
			if (in_pipe && sig == SIGINT)
				ft_dprintf(2, "\n");
		}
		if (!in_pipe)
			ft_dprintf(2, "\n");
		return (sig + 128);
	}
	else if (WIFSTOPPED(wait_status))
		return (WSTOPSIG(wait_status) + 128);
	else if (WIFEXITED(wait_status))
		return (WEXITSTATUS(wait_status));
	else if (WIFCONTINUED(wait_status))
		return (0);
	return (-1);
}

int	msh_exec_status(int wait_status)
{
	return (msh_exec_status_impl(wait_status, false));
}
