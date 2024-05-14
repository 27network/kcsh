/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_prompt_bash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:10:25 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/14 18:01:30 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <ft/string.h>
#include <msh/minishell.h>
#include <msh/env.h>
#include <msh/io.h>
#include <stdlib.h>
#include <unistd.h>

//TODO: Parse PS1 and PS2 variables
char	*msh_prompt_bash(t_minishell *msh)
{
	char	*user;
	char	*home;
	char	*cwd;
	char	*format;
	char	sep;

	user = msh_env_get(msh, "USER");
	home = msh_env_get(msh, "HOME");
	if (!user || !home)
		return (ft_strdup(MSH_DEFAULT_NAME"-"MSH_VERSION"$ "));
	sep = '$';
	if (ft_strncmp(user, "root", 5) == 0)
		sep = '#';
	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = ft_strdup("?");
	if (ft_strchr(cwd, '/'))
		format = ft_format("[%s@%s %s]%c ", user, msh_get_hostname(msh),
				ft_strrchr(cwd, '/') + 1, sep);
	else
		format = ft_format("[%s@%s %s]%c ", user, msh_get_hostname(msh),
				cwd, sep);
	free(cwd);
	return (format);
}
