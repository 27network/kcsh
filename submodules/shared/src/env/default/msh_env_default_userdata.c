/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_default_userdata.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:49:56 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/29 23:30:21 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/env.h>
#include <msh/util.h>
#include <pwd.h>

void	msh_env_setup_userdata(t_minishell *msh, int uid)
{
	struct passwd	pwd;

	pwd = msh_getpwuid(msh, uid);
	if (pwd.pw_name)
	{
		msh_env_set_if_not(msh, "HOME", ft_strdup(pwd.pw_dir),
			ENV_ALLOC_VALUE);
		msh_env_set_if_not(msh, "USER", ft_strdup(pwd.pw_name),
			ENV_ALLOC_VALUE);
		msh_env_set_if_not(msh, "SHELL", ft_strdup(pwd.pw_shell),
			ENV_ALLOC_VALUE);
		msh_passwd_free(&pwd);
	}
	else
	{
		msh_env_set_if_not(msh, "HOME", "/", 0);
		msh_env_set_if_not(msh, "USER", "user", 0);
		msh_env_set_if_not(msh, "SHELL", "/bin/sh", 0);
	}
}
