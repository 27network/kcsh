/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_shell_prompt_parse.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouchet <ebouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:10:25 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/21 01:22:07 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <ft/string.h>
#include <msh/minishell.h>
#include <msh/env.h>
#include <msh/util.h>
#include <stdlib.h>
#include <unistd.h>

//TODO: Parse PS1
//This is equivalent to [\u@\h \W]\$
char	*msh_shell_prompt_parse(t_minishell *msh)
{
	char	*uid;
	char	*user;
	char	*cwd;
	char	*format;
	char	sep;

	uid = msh_env_value(msh, "UID");
	user = msh_env_value(msh, "USER");
	sep = '$';
	if (uid && !ft_strcmp(uid, "0"))
		sep = '#';
	cwd = (char *) msh->execution_context.cwd;
	if (!cwd)
		cwd = "?";
	if (ft_strcmp(cwd, "/") && ft_strchr(cwd, '/'))
		format = ft_format("[%s@%s %s]%c ", user, msh_get_hostname(msh),
				ft_strrchr(cwd, '/') + 1, sep);
	else
		format = ft_format("[%s@%s %s]%c ", user, msh_get_hostname(msh),
				cwd, sep);
	return (format);
}
