/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd_home.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:25:47 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/15 19:31:06 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/env.h>
#include <msh/log.h>

int	msh_cd_absolute(t_minishell *msh, const char *target);

int	msh_cd_home(t_minishell *msh)
{
	const char	*target;

	target = msh_env_value(msh, "HOME");
	if (!target)
	{
		msh_error(msh, "cd: HOME not set\n");
		return (1);
	}
	return (msh_cd_absolute(msh, target));
}
