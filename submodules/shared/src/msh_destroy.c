/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:55:20 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/08 21:21:14 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <msh/minishell.h>
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
	if (msh->execution_context.cwd)
		free((char *) msh->execution_context.cwd);
	msh_env_free_all(msh);
}
