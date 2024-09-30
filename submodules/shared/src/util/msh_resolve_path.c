/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_resolve_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 01:44:08 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/30 15:52:58 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/print.h>
#include <ft/string.h>
#include <msh/minishell.h>
#include <msh/env.h>
#include <msh/util.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define INTERNAL_PATH "/run/current-system/sw/bin:\
/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

static bool	msh_validate(const char *filename)
{
	struct stat	st;

	if (ft_strstr(filename, "(nil)"))
		return (false);
	if (stat(filename, &st) < 0)
		return (false);
	if (S_ISDIR(st.st_mode))
		return (false);
	if (access(filename, X_OK) < 0)
		return (false);
	return (true);
}

static char	*msh_resolve_executable(t_minishell *msh, const char *file,
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
				current = ft_format("%s/%s", msh->execution_context.cwd, file);
			else
				current = ft_format("%s/%s", dirs[i], file);
			if (current && msh_validate(current))
				found = current;
			else if (current)
				free(current);
		}
		i++;
	}
	return (found);
}

char	*msh_resolve_path_impl(t_minishell *msh, const char *filename,
			char *path)
{
	char	**dirs;
	size_t	i;

	if (filename[0] == '/' || ft_strchr(filename, '/'))
		return (ft_strdup(filename));
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

char	*msh_resolve_path(t_minishell *msh, const char *filename)
{
	char	*path;

	path = msh_env_value(msh, "PATH");
	if (!path || !*path)
		path = ".";
	return (msh_resolve_path_impl(msh, filename, path));
}

char	*msh_resolve_path_internal(t_minishell *msh, const char *filename)
{
	char	*resolved;

	resolved = msh_resolve_path(msh, filename);
	if (!resolved)
		resolved = msh_resolve_path_impl(msh, filename, INTERNAL_PATH);
	return (resolved);
}
