/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_input_forked.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 07:16:26 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/18 13:34:42 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <ft/io.h>
#include <ft/mem.h>
#include <ft/print.h>
#include <ft/string.h>
#include <msh/cli/input.h>
#include <msh/features.h>
#include <msh/log.h>
#include <msh/signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#if FEAT_NO_READLINE
# include <shakespeare.h>
# define LINEREADER shakespeare
#else
# include <readline/readline.h>
# define LINEREADER readline
#endif // FEAT_NO_READLINE

#define BUFFER_SIZE 8192

static void	msh_forked_write(t_minishell *msh, const int fds[2],
				const char *interactive_prompt)
{
	char	*line;

	close(fds[0]);
	msh->interactive = true;
	msh_signal_init(msh, true);
	line = LINEREADER(interactive_prompt);
	if (line)
	{
		ft_putstr_fd(line, fds[1]);
		ft_putstr_fd("\n", fds[1]);
		free(line);
	}
	close(fds[1]);
}

static char	*msh_forked_read_whole(int fd)
{
	char	tmp[BUFFER_SIZE + 1];
	char	*buffer;
	ssize_t	n_bytes;

	buffer = NULL;
	while (1)
	{
		ft_bzero(tmp, BUFFER_SIZE + 1);
		n_bytes = read(fd, tmp, BUFFER_SIZE);
		if (n_bytes == -1)
			ft_strdel(&buffer);
		if (n_bytes <= 0)
			break ;
		buffer = ft_strjoins(2, "", 0b10, buffer, tmp);
		if (!buffer)
			break ;
		if (n_bytes < BUFFER_SIZE)
			break ;
	}
	close(fd);
	return (buffer);
}

static t_input_result	msh_forked_read(t_minishell *msh, int fd)
{
	char	*buffer;
	size_t	size;

	buffer = msh_forked_read_whole(fd);
	msh->interactive = true;
	msh_signal_init(msh, false);
	(void) msh;
	if (g_signal == SIGINT)
	{
		g_signal = -1;
		ft_strdel(&buffer);
		return ((t_input_result){.type = INPUT_INTERRUPTED, .buffer = NULL});
	}
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
	if (pid == 0)
	{
		msh_forked_write(msh, fds, interactive_prompt);
		return ((t_input_result){.type = INPUT_OK, .buffer = NULL});
	}
	msh->interactive = false;
	msh_signal_init(msh, false);
	g_signal = -1;
	waitpid(pid, NULL, 0);
	close(fds[1]);
	return (msh_forked_read(msh, fds[0]));
}

t_input_result	msh_input_forked(t_minishell *msh,
					const char *interactive_prompt)
{
	const t_input_result	error = {.type = INPUT_ERROR, .buffer = NULL};
	int						fds[2];
	pid_t					pid;
	t_input_result			result;

	if (!interactive_prompt)
		interactive_prompt = "> ";
	if (pipe(fds) == -1)
	{
		msh_error(msh, "msh_input_forked: pipe: %s\n", strerror(errno));
		return (error);
	}
	pid = msh_fork(msh);
	if (pid == -1)
	{
		msh_error(msh, "msh_input_forked: fork: %s\n", strerror(errno));
		return (error);
	}
	result = msh_input_forked0(msh, fds, pid, interactive_prompt);
	msh_log(msh, MSG_DEBUG_GENERIC, "result = { buffer: \"%s\", type: %s }\n",
		result.buffer, msh_input_type(result.type));
	return (result);
}
