/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_set_cwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 20:45:39 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/08 20:48:07 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/env.h>
#include <msh/util.h>

void	msh_set_cwd(t_minishell *msh, char *cwd)
{
	if (!cwd)
	{
		msh_warn(msh, "msh_set_cwd: provided cwd is NULL, using getcwd\n");
		cwd = getcwd(NULL, 0);
	}
	if (msh->execution_context.cwd)
		free(msh->execution_context.cwd);
	msh->execution_context.cwd = cwd;
}
