/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_resolve_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 01:44:08 by kiroussa          #+#    #+#             */
/*   Updated: 2024/03/22 17:58:34 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <ft/string.h>
#include <msh/minishell.h>
#include <msh/env.h>
#include <stdlib.h>
#include <unistd.h>

static bool	msh_validate(const char *filename)
{
	return (access(filename, X_OK) == 0);
}

static char	*msh_resolve_executable(const char *filename, char **dirs)
{
	size_t	i;
	char	*found;
	char	*current;

	i = 0;
	found = NULL;
	while (dirs[i])
	{
		if (!found)
		{
			current = ft_format("%s/%s", dirs[i], filename);
			if (current && msh_validate(current))
				found = current;
			else if (current)
				free(current);
		}
		free(dirs[i]);
		i++;
	}
	free(dirs);
	return (found);
}

char	*msh_resolve_path(t_minishell *msh, const char *filename)
{
	char	*path;
	char	**dirs;

	if (filename[0] == '/' || ft_strchr(filename, '/'))
		return (ft_strdup(filename));
	path = msh_env_get(msh, "PATH");
	if (!path)
		return (ft_strdup(filename));
	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	path = msh_resolve_executable(filename, dirs);
	if (!path)
		return (ft_strdup(filename));
	return (path);
}
