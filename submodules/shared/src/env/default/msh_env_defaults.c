/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_defaults.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 23:15:34 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/07 08:33:53 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string/parse.h>
#include <ft/string.h>
#include <msh/env.h>
#include <msh/util.h>
#include <pwd.h>
#include <sys/stat.h>
#include <unistd.h>

static void	msh_env_setup_userdata(t_minishell *msh, int uid)
{
	struct passwd	pwd;

	pwd = msh_getpwuid(msh, uid);
	if (pwd.pw_name)
	{
		msh_env_set_if_not(msh, "HOME", ft_strdup(pwd.pw_dir),
			ENV_ALLOC_VALUE);
		msh_env_set_if_not(msh, "SHELL", ft_strdup(pwd.pw_shell),
			ENV_ALLOC_VALUE);
		msh_passwd_free(&pwd);
	}
	else
	{
		msh_env_set_if_not(msh, "HOME", "/", 0);
		msh_env_set_if_not(msh, "SHELL", "/bin/sh", 0);
	}
}

static void	msh_handle_pwd_import(t_minishell *msh, t_variable *v_pwd,
				char *pwd, char *home)
{
	char	*curr;

	if (v_pwd && v_pwd->flags & ENV_IMPORTED && pwd && *pwd == '/'
		&& msh_same_file(pwd, ".", NULL, NULL))
	{
		curr = msh_canonicalize(pwd);
		if (!curr)
			curr = getcwd(NULL, 0);
		else if (chdir(curr) < 0)
			curr = getcwd(NULL, 0);
		msh_env_push(msh, "PWD", curr, ENV_ALLOC_VALUE | ENV_EXPORTED);
	}
	else if (home && msh->interactive && msh->flags.login
		&& msh_same_file(home, ".", NULL, NULL))
	{
		if (chdir(home) < 0)
			home = getcwd(NULL, 0);
		msh_env_push(msh, "PWD", ft_strdup(home), ENV_ALLOC_VALUE
			| ENV_EXPORTED);
	}
	else
		msh_env_push(msh, "PWD", getcwd(NULL, 0), ENV_ALLOC_VALUE
			| ENV_EXPORTED);
}

static void	msh_env_setup_pwd(t_minishell *msh)
{
	t_variable	*v_pwd;
	char		*pwd;
	char		*home;
	char		*oldpwd;

	v_pwd = msh_env_find(msh, "PWD");
	pwd = msh_env_value(msh, "PWD");
	home = msh_env_value(msh, "HOME");
	msh_handle_pwd_import(msh, v_pwd, pwd, home);
	oldpwd = msh_env_value(msh, "OLDPWD");
	if (!oldpwd || !*oldpwd || !msh_is_directory(oldpwd))
		msh_env_push(msh, "OLDPWD", NULL, ENV_INVISIBLE | ENV_EXPORTED);
}

static void	msh_env_adjust_shlvl(t_minishell *msh, int change)
{
	char		*old_shlvl;
	int			shlvl;

	old_shlvl = msh_env_value(msh, "SHLVL");
	if (!old_shlvl || !*old_shlvl)
		old_shlvl = "0";
	shlvl = ft_atoi(old_shlvl);
	shlvl += change;
	if (shlvl < 0)
		shlvl = 0;
	else if (shlvl >= 1000)
		shlvl = 1;
	msh_env_push(msh, "SHLVL", ft_itoa(shlvl), ENV_EXPORTED | ENV_ALLOC_VALUE);
}

void	msh_env_defaults(t_minishell *msh)
{
	const int	uid = msh_getuid(msh);

	msh_env_setup_userdata(msh, uid);
	msh_env_setup_pwd(msh);
	msh_env_set_if_not(msh, "PATH", ENV_DEFAULT_PATH, 0);
	msh_env_set_if_not(msh, "TERM", ENV_DEFAULT_TERM, 0);
	msh_env_set_if_not(msh, "PS1", ENV_DEFAULT_PS1, 0);
	msh_env_set_if_not(msh, "PS2", ENV_DEFAULT_PS2, 0);
	msh_env_set_if_not(msh, "PS3", ENV_DEFAULT_PS3, 0);
	msh_env_set_if_not(msh, "PS4", ENV_DEFAULT_PS4, 0);
	msh_env_set_if_not(msh, "HISTFILE", msh_expand_tilde(msh,
			ENV_DEFAULT_HISTFILE), ENV_ALLOC_VALUE);
	msh_env_set_if_not(msh, "HISTFILESIZE", ft_itoa(ENV_DEFAULT_HISTFILESIZE),
		ENV_ALLOC_VALUE);
	msh_env_set_if_not(msh, "HISTSIZE", ft_itoa(ENV_DEFAULT_HISTSIZE),
		ENV_ALLOC_VALUE);
	msh_env_push(msh, "IFS", ENV_DEFAULT_IFS, 0);
	msh_env_set_if_not(msh, "UID", ft_itoa(uid), ENV_ALLOC_VALUE);
	msh_env_set_if_not(msh, "EUID", ft_itoa(msh_geteuid(msh)), ENV_ALLOC_VALUE);
	msh_env_set_if_not(msh, "HOSTTYPE", msh_get_hosttype(msh), ENV_ALLOC_VALUE);
	msh_env_adjust_shlvl(msh, 1);
	msh_env_set_if_not(msh, "_", msh->binary_name, ENV_EXPORTED
		| ENV_INVISIBLE);
}
