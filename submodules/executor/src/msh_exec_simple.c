/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_simple.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 07:43:19 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/19 02:49:08 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <msh/signal.h> 
#include <errno.h>
#include <ft/print.h>
#include <ft/string.h>
#include <msh/env.h>
#include <msh/builtin.h>
#include <msh/exec/exec.h>
#include <msh/io.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHOULD_EXIT -1
#define BUILTIN_NOT_FOUND -2

static void	msh_exec_error(t_minishell *msh, int err, char *name)
{
	if (ft_strchr(name, '/'))
	{
		if (msh_is_directory(name))
			msh_error(msh, "%s: %s\n", name, strerror(EISDIR));
		else
			msh_error(msh, "%s: %s\n", name, strerror(err));
	}
	else
		msh_warn(msh, "%s: command not found\n", name);
}

static int	msh_exec(
	t_minishell *msh,
	char *binary_path,
	char **av,
	char **envp
) {
	pid_t	pid;
	int		status;

	msh->interactive = false;
	status = -1;
	pid = fork();
	if (pid == 0)
	{
		msh_signal_setdfl();
		if (execve(binary_path, av, envp) == -1)
			msh_exec_error(msh, errno, av[0]);
		msh->execution_context.running = false;
		return (1);
	}
	else if (pid < 0)
		msh_error(msh, "%s: %m\n", binary_path);
	else
	{
		msh_signal_init(msh);
		if (waitpid(pid, &status, 0) < 0)
			msh_error(msh, "%s: %m\n", binary_path);
	}
	return (msh_exec_status(status));
}

int	msh_exec_builtin(t_minishell *msh, char **args, char **env)
{
	const t_builtin	*builtin = msh_builtin_get(args[0]);
	bool			n_env;
	bool			n_msh;
	int				argc;
	int				status;

	if (builtin && builtin->enabled)
	{
		argc = 0;
		while (args[argc])
			argc++;
		n_env = (builtin->needs & NEEDS_ENV) == NEEDS_ENV;
		n_msh = (builtin->needs & NEEDS_MSH) == NEEDS_MSH;
		if (n_env && n_msh)
			status = ((t_builtin_fboth)builtin->func)(argc, args, env, msh);
		else if (n_env)
			status = ((t_builtin_fenv)builtin->func)(argc, args, env);
		else if (n_msh)
			status = ((t_builtin_fmsh)builtin->func)(argc, args, msh);
		else
			status = ((t_builtin_fnone)builtin->func)(argc, args);
		msh_env_tab_free(env);
		return (status);
	}
	return (BUILTIN_NOT_FOUND);
}

int	msh_exec_simple(t_minishell *msh, char **args)
{
	int		status;
	char	**env;
	char	*path;
	bool	old_interactive;

	if (!args[0])
		return (0);
	env = msh_env_tab(msh);
	status = msh_exec_builtin(msh, args, env);
	if (status != BUILTIN_NOT_FOUND)
		return (status);
	if (*args[0] != '.' && !ft_strchr(args[0], '/'))
		path = msh_resolve_path(msh, args[0]);
	else
		path = ft_strdup(args[0]);
	old_interactive = msh->interactive;
	if (path)
		status = msh_exec(msh, path, args, env);
	if (path)
		free(path);
	msh->interactive = old_interactive;
	msh_signal_init(msh);
	msh_env_tab_free(env);
	return (status);
}
