/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_simple.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 07:43:19 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/06 20:47:24 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/signal.h> 
#include <errno.h>
#include <ft/print.h>
#include <ft/string.h>
#define _GNU_SOURCE
#include <msh/env.h>
#include <msh/exec/builtin.h>
#include <msh/exec/exec.h>
#include <msh/io.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHOULD_EXIT -1
#define BUILTIN_NOT_FOUND -2

static void	msh_exec_error(t_minishell *msh, int err, char *name)
{
	if (ft_strchr(name, '/'))
	{
		if (msh_is_directory(name))
			ft_dprintf(2, "%s: %s: %s\n", msh->name, name, strerror(EISDIR));
		else
			ft_dprintf(2, "%s: %s: %s\n", msh->name, name, strerror(err));
	}
	else
		ft_dprintf(2, "%s: command not found\n", name);
}

static int	msh_exec_status(int wait_status)
{
	int	sig;

	if (WIFEXITED(wait_status))
		return (WEXITSTATUS(wait_status));
	else if (WIFSIGNALED(wait_status))
	{
		sig = WTERMSIG(wait_status);
		if (sig != SIGINT)
			ft_dprintf(2, "Terminated by signal %d\n", WTERMSIG(wait_status));
		return (sig + 128);
	}
	else if (WIFSTOPPED(wait_status))
		return (WSTOPSIG(wait_status) + 128);
	return (SHOULD_EXIT);
}

static int	msh_exec(
	t_minishell *msh,
	char *binary_path,
	char **av,
	char **envp
) {
	pid_t	pid;
	int		status;

	status = -1;
	pid = fork();
	if (pid == 0)
	{
		msh_signal_setdfl();
		if (execve(binary_path, av, envp) == -1)
			msh_exec_error(msh, errno, av[0]);
		return (SHOULD_EXIT);
	}
	else if (pid < 0)
		ft_dprintf(2, "%s: %s: %m\n", msh->name, binary_path);
	else
	{
		if (waitpid(pid, &status, 0) < 0)
			ft_dprintf(2, "%s: %s: %m\n", msh->name, binary_path);
	}
	return (msh_exec_status(status));
}

int	msh_exec_builtin(t_minishell *msh, char **args, char **env)
{
	t_builtin	*builtin;
	bool		n_env;
	bool		n_msh;
	int			argc;

	builtin = msh_builtin_get(args[0]);
	if (builtin)
	{
		argc = 0;
		while (args[argc])
			argc++;
		n_env = (builtin->needs & NEEDS_ENV) == NEEDS_ENV;
		n_msh = (builtin->needs & NEEDS_MSH) == NEEDS_MSH;
		if (n_env && n_msh)
			return (((t_builtin_fboth)builtin->func)(argc, args, env, msh));
		else if (n_env)
			return (((t_builtin_fenv)builtin->func)(argc, args, env));
		else if (n_msh)
			return (((t_builtin_fmsh)builtin->func)(argc, args, msh));
		else
			return (((t_builtin_fnone)builtin->func)(argc, args));
	}
	return (BUILTIN_NOT_FOUND);
}

int	msh_exec_simple(t_minishell *msh, char **args)
{
	int		status;
	char	**env;
	char	*path;

	env = msh_env_tab(msh);
	status = msh_exec_builtin(msh, args, env);
	if (status != BUILTIN_NOT_FOUND)
	{
		msh_env_tab_free(env);
		return (status);
	}
	if (!args[0])
		return (0);
	if (*args[0] != '.' && !ft_strchr(args[0], '/'))
		path = msh_resolve_path(msh, args[0]);
	else
		path = ft_strdup(args[0]);
	if (path)
	{
		status = msh_exec(msh, path, args, env);
		free(path);
	}
	msh_env_tab_free(env);
	return (status);
}
