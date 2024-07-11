/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_shell_prompt_parse.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouchet <ebouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:10:25 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/09 15:50:34 by ebouchet         ###   ########.fr       */
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
	char	*user;
	char	*home;
	char	*cwd;
	char	*format;
	char	sep;

	user = msh_env_value(msh, "USER");
	home = msh_env_value(msh, "HOME");
	if (!user || !home)
		return (ft_strdup(MSH_DEFAULT_NAME"-"MSH_VERSION"$ "));
	sep = '$';
	if (msh_geteuid(msh) == 0)
		sep = '#';
	cwd = (char *) msh->execution_context.cwd;
	if (!cwd)
		cwd = "?";
	if (ft_strchr(cwd, '/'))
		format = ft_format("[%s@%s %s]%c ", user, msh_get_hostname(msh),
				ft_strrchr(cwd, '/') + 1, sep);
	else
		format = ft_format("[%s@%s %s]%c ", user, msh_get_hostname(msh),
				cwd, sep);
	return (format);
}
