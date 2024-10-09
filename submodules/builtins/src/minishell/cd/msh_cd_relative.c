/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd_relative.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:28:47 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/08 19:06:45 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <ft/mem.h>
#include <ft/string.h>
#include <msh/env.h>
#include <msh/log.h>
#include <msh/util.h>
#include <string.h>
#include <unistd.h>

/**
 * Yes, this is a code repeat from `msh_cd_absolute`, yes it's ugly,
 * but I don't care, I have a week to finish this.
 */
static int	msh_cd_target(t_minishell *msh, const char *target,
	const char *arg)
{
	int	ret;

	ret = chdir(target);
	if (ret == 0 && msh->execution_context.cwd)
		ret = chdir(msh->execution_context.cwd);
	if (ret != 0)
		msh_error(msh, "cd: %s: %s\n", arg, strerror(errno));
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
		ret = chdir(target);
	if (ret == 0)
		msh_set_cwd(msh, target);
	else
		msh_error(msh, "cd: %s: %s\n", target, strerror(errno));
	if (ret != 0 && target)
		free((void *) target);
	return (ret != 0 || target == NULL);
}

int	msh_cd_relative(t_minishell *msh, const char *arg)
{
	const char	*cwd = msh->execution_context.cwd;
	char		*target;
	int			ret;

	if (!arg)
		return (1);
	if (msh_env_value(msh, "CDPATH"))
		msh_warn(msh, "cd: CDPATH is not supported yet\n");
	target = ft_calloc(ft_strlen(cwd) + ft_strlen(arg) + 2, sizeof(char));
	if (!target)
		msh_error(msh, "cd: allocation error\n");
	if (!target)
		return (1);
	ft_strcpy(target, cwd);
	ft_strcat(target, "/");
	ft_strcat(target, arg);
	ret = msh_cd_target(msh, target, arg);
	free(target);
	return (ret);
}
