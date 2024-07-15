/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd_relative.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:28:47 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/15 19:51:32 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <msh/log.h>
#include <msh/util.h>
#include <unistd.h>

int	msh_cd_absolute(t_minishell *msh, const char *target);

//TODO(kiroussa): fix output error
int	msh_cd_relative(t_minishell *msh, const char *arg)
{
	const char	*cwd = msh->execution_context.cwd;
	char		*target;
	int			ret;

	if (!arg)
		return (1);
	target = ft_calloc(ft_strlen(cwd) + ft_strlen(arg) + 2, sizeof(char));
	if (!target)
		msh_error(msh, "cd: allocation error\n");
	if (!target)
		return (1);
	ft_strcpy(target, cwd);
	ft_strcat(target, "/");
	ft_strcat(target, arg);
	ret = msh_cd_absolute(msh, target);
	free(target);
	return (ret);
}
