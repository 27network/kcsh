/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd_oldpwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:29:27 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/15 19:40:52 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <ft/string.h>
#include <msh/env.h>
#include <msh/log.h>
#include <msh/util.h>
#include <string.h>
#include <unistd.h>

int	msh_cd_oldpwd(t_minishell *msh)
{
	const char	*target;
	int			ret;

	target = msh_env_value(msh, "OLDPWD");
	if (!target)
		msh_error(msh, "cd: OLDPWD not set\n");
	if (!target)
		return (1);
	ret = chdir(target);
	if (ret != 0)
		msh_error(msh, "cd: %s: %s\n", target, strerror(errno));
	else
		msh_set_cwd(msh, ft_strdup(target));
	return (ret);
}
