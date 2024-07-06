/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_geteuid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 23:38:19 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/07 00:31:26 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string/parse.h>
#include <ft/string.h>
#include <msh/util.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

static int	msh_geteuid_exec(t_minishell *msh, char *bin, int fds[2],
				char *result)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		dup2(fds[1], 1);
		close(fds[0]);
		close(fds[1]);
		execve(bin, (char *[]){bin, "-ru", NULL}, NULL);
		(void) write(1, "-1", 2);
		msh_exit(msh, 1);
		return (0);
	}
	waitpid(pid, &status, 0);
	if (read(fds[0], result, 1024) <= 0)
		return (0);
	return (1);
}

int	msh_geteuid(t_minishell *msh)
{
	char	*path;
	int		fds[2];
	char	result[1024];

	if (pipe(fds) == -1)
		return (-1);
	path = msh_resolve_path(msh, "id");
	ft_bzero(result, 1024);
	ft_strcpy(result, "-1");
	if (path && !msh_geteuid_exec(msh, path, fds, result))
		ft_strcpy(result, "-1");
	close(fds[0]);
	close(fds[1]);
	if (path)
		free(path);
	return ((int) ft_atoll(result));
}
