/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_getpw_for.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:49:47 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/07 04:13:14 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <ft/mem.h>
#include <ft/string.h>
#include <msh/util.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

bool	msh_passwd_find(struct passwd *pwd, int fd,
			uid_t uid, const char *name);

static int	msh_getent_passwd_exec(t_minishell *msh, char **args, int fds[2],
				const char *name)
{
	pid_t	pid;
	int		status;

	pid = msh_fork(msh);
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		dup2(fds[1], 1);
		close(fds[0]);
		close(fds[1]);
		execve(args[0], args, NULL);
		close(1);
		free(args[0]);
		if (name)
			free((void *)name);
		msh_exit(msh, 1);
		return (-1);
	}
	waitpid(pid, &status, 0);
	close(fds[1]);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		return (0);
	return (1);
}

static bool	msh_getent_passwd(t_minishell *msh, struct passwd *pwd,
				uid_t uid, const char *name)
{
	char	*path;
	int		fds[2];
	bool	ret;

	if (pipe(fds) == -1)
		return (false);
	path = msh_resolve_path(msh, "getent");
	if (!path)
		return (false);
	if (!msh_getent_passwd_exec(msh, (char *[]){path, "passwd", NULL},
		fds, name))
	{
		close(fds[0]);
		free(path);
		return (false);
	}
	ret = msh_passwd_find(pwd, fds[0], uid, name);
	free(path);
	return (ret);
}

struct passwd	msh_getpw_for(t_minishell *msh, uid_t uid, const char *name)
{
	struct passwd	pwd;
	int				fd;

	ft_bzero(&pwd, sizeof(pwd));
	fd = open("/etc/passwd", O_RDONLY);
	if (fd != -1 && msh_passwd_find(&pwd, fd, uid, name))
		return (pwd);
	ft_bzero(&pwd, sizeof(pwd));
	if (msh_getent_passwd(msh, &pwd, uid, name))
		return (pwd);
	ft_bzero(&pwd, sizeof(pwd));
	return (pwd);
}
