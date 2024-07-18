/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_geteuid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 23:38:19 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/18 03:01:57 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string/parse.h>
#include <ft/string.h>
#include <msh/features.h>
#include <msh/util.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

static int	msh_geteuid_exec(t_minishell *msh, char **args, int fds[2],
				char *result)
{
	pid_t	pid;
	int		status;

	ft_bzero(result, 1024);
	pid = msh_fork(msh);
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		dup2(fds[1], 1);
		close(fds[0]);
		close(fds[1]);
		execve(args[0], args, NULL);
		free(args[0]);
		(void) write(1, "-1", 2);
		msh_exit(msh, 1);
		return (0);
	}
	waitpid(pid, &status, 0);
	if (read(fds[0], result, 1024) <= 0)
		return (0);
	return (1);
}

int	msh_uid(t_minishell *msh, bool real)
{
	char	*path;
	int		fds[2];
	char	result[1024];
	char	*flags;

	flags = "-u";
	if (real)
		flags = "-ru";
	path = msh_resolve_path(msh, "id");
	if (!path)
		return (-1);
	if (pipe(fds) == -1)
	{
		free(path);
		return (-1);
	}
	if (path && !msh_geteuid_exec(msh, (char *[]){path, flags, NULL},
		fds, result))
		ft_strcpy(result, "-1");
	close(fds[0]);
	close(fds[1]);
	if (path)
		free(path);
	return ((int) ft_atoll(result));
}

int	msh_geteuid_internal(t_minishell *msh)
{
	return (msh_uid(msh, false));
}

#if !FEAT_SYSCALLS
# define TARGET msh_geteuid_internal
#else
# define TARGET msh_geteuid_syscall

int	msh_geteuid_syscall(t_minishell *msh)
{
	int	id;

	id = geteuid();
	if (id == -1)
		return (msh_geteuid_internal(msh));
	return (id);
}

#endif // !FEAT_SYSCALLS

int	msh_geteuid(t_minishell *msh)
{
	return (TARGET(msh));
}
