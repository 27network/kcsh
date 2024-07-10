/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_default_pwd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:32:51 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/10 17:54:45 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/env.h>
#include <msh/util.h>
#include <pwd.h>
#include <sys/stat.h>
#include <unistd.h>

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

void	msh_env_setup_pwd(t_minishell *msh)
{
	t_variable	*v_pwd;
	char		*pwd;
	char		*home;
	char		*oldpwd;
	t_variable	*v_oldpwd;

	v_pwd = msh_env_find(msh, "PWD");
	pwd = msh_env_value(msh, "PWD");
	home = msh_env_value(msh, "HOME");
	msh_handle_pwd_import(msh, v_pwd, pwd, home);
	oldpwd = msh_env_value(msh, "OLDPWD");
	if (!oldpwd || !*oldpwd || !msh_is_directory(oldpwd))
	{
		msh_env_push(msh, "OLDPWD", NULL, ENV_EXPORTED);
		v_oldpwd = msh_env_find(msh, "OLDPWD");
		if (v_oldpwd)
			v_oldpwd->flags &= ~(ENV_ALLOC_VALUE);
	}
}
