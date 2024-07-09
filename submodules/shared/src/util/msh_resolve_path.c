/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_resolve_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 01:44:08 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/09 14:01:36 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/print.h>
#include <ft/string.h>
#include <msh/minishell.h>
#include <msh/env.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

static bool	msh_validate(const char *filename)
{
	struct stat	st;

	if (stat(filename, &st) < 0)
		return (false);
	if (S_ISDIR(st.st_mode))
		return (false);
	if (access(filename, X_OK) < 0)
		return (false);
	return (true);
}

static char	*msh_resolve_executable(t_minishell *msh, const char *filename,
				char **dirs)
{
	size_t	i;
	char	*found;
	char	*current;

	i = 0;
	found = NULL;
	while (dirs[i])
	{
		if (!found && *dirs[i])
		{
			if (!ft_strcmp(dirs[i], "."))
				current = ft_format("%s/%s", msh->execution_context.cwd,
						filename);
			else
				current = ft_format("%s/%s", dirs[i], filename);
			if (current && msh_validate(current))
				found = current;
			else if (current)
				free(current);
		}
		i++;
	}
	return (found);
}

char	*msh_resolve_path(t_minishell *msh, const char *filename)
{
	char	*path;
	char	**dirs;
	size_t	i;

	if (filename[0] == '/' || ft_strchr(filename, '/'))
		return (ft_strdup(filename));
	path = msh_env_value(msh, "PATH");
	if (!path || !*path)
		path = ".";
	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	path = msh_resolve_executable(msh, filename, dirs);
	i = 0;
	while (dirs[i])
		free(dirs[i++]);
	free(dirs);
	if (path && path[0] == '.' && path[1] == '/')
		ft_memmove(path, path + 2, ft_strlen(path + 2) + 1);
	return (path);
}
