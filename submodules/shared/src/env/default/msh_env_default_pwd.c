/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_default_pwd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:32:51 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/15 18:32:25 by kiroussa         ###   ########.fr       */
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
		if (!curr || chdir(curr) < 0)
			curr = NULL;
		msh_set_cwd(msh, curr);
	}
	else if (home && msh->interactive && msh->flags.login
		&& msh_same_file(home, ".", NULL, NULL))
	{
		home = ft_strdup(home);
		if (!home || chdir(home) < 0)
			home = NULL;
		msh_set_cwd(msh, home);
	}
	else
		msh_set_cwd(msh, NULL);
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
