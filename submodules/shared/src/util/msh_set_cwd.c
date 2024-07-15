/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_set_cwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouchet <ebouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 20:45:39 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/15 18:37:10 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/env.h>
#include <msh/log.h>
#include <msh/util.h>
#include <stdlib.h>
#include <unistd.h>

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
		ft_strdel((char **) &msh->execution_context.cwd);
	msh->execution_context.cwd = cwd;
	msh_env_push(msh, "PWD", cwd, ENV_EXPORTED);
	v_pwd = msh_env_find(msh, "PWD");
	if (v_pwd)
		v_pwd->flags &= ~(ENV_ALLOC_VALUE);
}
