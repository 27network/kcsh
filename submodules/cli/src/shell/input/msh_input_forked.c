/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_input_forked.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 07:16:26 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/28 19:23:44 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <ft/io.h>
#include <ft/print.h>
#include <ft/string.h>
#include <msh/cli/input.h>
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

static t_input_result	msh_forked_read(int fd)
{
	char	*buffer;
	size_t	size;

	buffer = get_next_line(fd);
	close(fd);
	if (!buffer)
		return ((t_input_result){.type = INPUT_EOF, .buffer = NULL});
	size = ft_strlen(buffer);
	if (size && buffer[size - 1] == '\n')
		return ((t_input_result){.type = INPUT_OK, .buffer = buffer});
	return ((t_input_result){.type = INPUT_EOF, .buffer = buffer});
}

static t_input_result	msh_input_forked0(t_minishell *msh,
							int fds[2], pid_t pid,
							const char *interactive_prompt)
{
	const bool	interactive = msh->interactive;

	msh->interactive = pid == 0;
	msh_signal_init(msh, true);
	if (pid == 0)
		msh_forked_write(msh, fds, interactive_prompt);
	if (pid == 0)
		return ((t_input_result){.type = INPUT_IGNORED, .buffer = NULL});
	waitpid(pid, NULL, 0);
	close(fds[1]);
	msh->interactive = interactive;
	return (msh_forked_read(fds[0]));
}

t_input_result	msh_input_forked(t_minishell *msh,
					const char *interactive_prompt)
{
	const t_input_result	error = {.type = INPUT_ERROR, .buffer = NULL};
	int						fds[2];
	pid_t					pid;

	if (pipe(fds) == -1)
	{
		msh_error(msh, "msh_input_forked: pipe: %s\n", strerror(errno));
		return (error);
	}
	pid = fork();
	if (pid == -1)
		msh_error(msh, "msh_input_forked: fork: %s\n", strerror(errno));
	if (pid == -1)
		return (error);
	return (msh_input_forked0(msh, fds, pid, interactive_prompt));
}
