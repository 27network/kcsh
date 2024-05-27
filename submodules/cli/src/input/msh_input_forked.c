/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_input_forked.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 07:16:26 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/27 07:48:36 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <ft/io.h>
#include <ft/print.h>
#include <msh/minishell.h>
#include <msh/log.h>
#include <msh/signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void	msh_forked_write(t_minishell *msh, const int fds[2],
				const char *interactive_prompt)
{
	char	*line;

	rl_catch_signals = 1;
	close(fds[0]);
	if (msh->interactive)
		line = readline(interactive_prompt);
	else
		line = get_next_line(msh->execution_context.file);
	if (line)
	{
		ft_putstr_fd(line, fds[1]);
		ft_putstr_fd("\n", fds[1]);
		free(line);
	}
	close(fds[1]);
	msh->interactive = false;
}

static char	*msh_forked_read(int status, int fd)
{
	char	*buffer;

	buffer = get_next_line(fd);
	close(fd);
	printf("read: %p\n", buffer);
	//TODO: figure out a dumb way to differentiate CTRL+C and EOF
	if (WIFEXITED(status))
	{
		printf("msh: child process exited with %d\n", WEXITSTATUS(status));
		free(buffer);
		return ((char *) 1);
	}
	return (buffer);
}

char	*msh_input_forked(t_minishell *msh, const char *interactive_prompt)
{
	const bool	interactive = msh->interactive;
	int			fds[2];
	pid_t		pid;
	int			status;

	if (pipe(fds) == -1)
	{
		msh_error(msh, "msh_input_forked: pipe: %s\n", strerror(errno));
		return (NULL);
	}
	pid = fork();
	msh->interactive = pid == 0;
	msh_signal_init(msh, true);
	if (pid == 0)
		msh_forked_write(msh, fds, interactive_prompt);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		close(fds[1]);
		msh->interactive = interactive;
		return (msh_forked_read(status, fds[0]));
	}
	else
		msh_error(msh, "msh_input_forked: fork: %s\n", strerror(errno));
	return (NULL);
}
