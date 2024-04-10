/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_run_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 01:41:40 by kiroussa          #+#    #+#             */
/*   Updated: 2024/04/10 19:23:18 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <ft/print.h>
#include <ft/string.h>
#include <msh/minishell.h>
#include <msh/io.h>
#include <msh/cli/runner.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int	msh_resolve_fd(t_minishell *msh, const char *filename, char **name)
{
	int		fd;
	char	*resolved;

	*name = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		resolved = msh_resolve_path(msh, filename);
		if (resolved)
		{
			fd = open(resolved, O_RDONLY);
			if (fd >= 0)
				*name = resolved;
			else
				free(resolved);
		}
	}
	else
		*name = ft_strdup((char *)filename);
	return (fd);
}

void	msh_run_file(
	t_minishell *msh,
	const char *filename,
	int argc,
	const char **argv
) {
	char	*resolved;
	int		fd;
	int		ret;

	ret = 0;
	msh->shell_args.argc = argc;
	msh->shell_args.argv = argv;
	fd = msh_resolve_fd(msh, filename, &resolved);
	if (fd < 0)
	{
		ft_dprintf(2, "%s: %s: %s\n", msh->name, filename, strerror(errno));
		if (resolved)
			free(resolved);
		msh_exit(msh, 127);
	}
	msh->name = resolved;
	if (msh_runner_check(msh, resolved, fd, &ret))
		ret = msh_run_script(msh, fd, filename);
	if (resolved)
		free(resolved);
	close(fd);
	msh_exit(msh, ret);
}
