/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_history_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:44:37 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/28 23:49:20 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <ft/string.h>
#include <msh/env.h>
#include <stdlib.h>
#include <unistd.h>

int	msh_history_file(t_minishell *msh, int flags)
{
	char	*home;
	char	*path;
	char	*filename;
	int		fd;

	home = msh_env_value(msh, "HOME");
	if (!home || !*home)
		return (-1);
	filename = MSH_HISTORY_FILE;
	if (home[ft_strlen(home) - 1] == '/')
		filename++;
	path = ft_strjoin(home, filename);
	fd = -1;
	if (path)
		fd = open(path, flags, 0644);
	if (path)
		free(path);
	if (fd < 0)
		return (-1);
	return (fd);
}
