/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouchet <ebouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:55:20 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/11 16:47:06 by ebouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <msh/log.h>
#include <msh/env.h>
#include <stdlib.h>
#include <unistd.h>

void	msh_destroy(t_minishell *msh)
{
	if (!msh)
	{
		ft_putendl_fd("msh_destroy: msh is NULL", STDERR_FILENO);
		exit(-1);
	}
	if (msh->execution_context.file != 0)
	{
		close(msh->execution_context.file);
		free((char *) msh->name);
	}
	msh_env_free_all(msh);
	if (msh->execution_context.cwd)
	{
		if (!msh->forked)
			msh_log(msh, MSG_DEBUG_GENERIC, "Freeing cwd (%s)\n",
				msh->execution_context.cwd);
		free((char *) msh->execution_context.cwd);
	}
}
