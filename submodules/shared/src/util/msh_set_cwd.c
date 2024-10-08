/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_set_cwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouchet <ebouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 20:45:39 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/01 17:13:33 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/env.h>
#include <msh/log.h>
#include <msh/util.h>
#include <stdlib.h>
#include <unistd.h>

static void	msh_update_oldpwd(t_minishell *msh, const char *oldpwd)
{
	char		*oldpwd_value;
	t_variable	*v_oldpwd;

	oldpwd_value = msh_env_value(msh, "OLDPWD");
	if (oldpwd_value)
		ft_strdel(&oldpwd_value);
	v_oldpwd = msh_env_get(msh, "OLDPWD", ENV_EXPORTED | ENV_ALLOC_VALUE);
	if (!v_oldpwd)
		ft_strdel((char **) &oldpwd);
	else
	{
		v_oldpwd->value = (char *) oldpwd;
		v_oldpwd->flags |= ENV_ALLOC_VALUE;
	}
}

void	msh_set_cwd(t_minishell *msh, const char *cwd)
{
	t_variable	*v_pwd;

	if (!cwd)
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
		{
			msh_error(msh, "couldn't getcwd (%m), exitting...\n");
			msh_exit(msh, 1);
		}
	}
	if (msh->execution_context.cwd)
		msh_update_oldpwd(msh, msh->execution_context.cwd);
	msh->execution_context.cwd = cwd;
	msh_env_push(msh, "PWD", cwd, ENV_EXPORTED);
	v_pwd = msh_env_find(msh, "PWD");
	if (v_pwd)
		v_pwd->flags &= ~(ENV_ALLOC_VALUE);
}
