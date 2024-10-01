/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd_absolute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:26:29 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/01 16:09:11 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <msh/env.h>
#include <msh/log.h>
#include <msh/util.h>
#include <string.h>
#include <unistd.h>

int	msh_cd_absolute(t_minishell *msh, const char *target)
{
	int	ret;

	if (!target)
		return (1);
	ret = chdir(target);
	if (ret != 0)
		msh_error(msh, "cd: %s: %s\n", target, strerror(errno));
	if (ret != 0)
		return (1);
	target = msh_canonicalize(target);
	if (!target)
		msh_warn(msh, "cd: couldn't canonicalize path, fallback to cwd\n");
	if (!target)
		target = getcwd(NULL, 0);
	if (!target)
		msh_error(msh, "cd: getcwd: allocation error\n");
	else
		msh_set_cwd(msh, target);
	return (ret != 0 || target == NULL);
}
