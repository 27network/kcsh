/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_run_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 01:41:40 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/21 19:18:24 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <ft/print.h>
#include <ft/string.h>
#include <msh/minishell.h>
#include <msh/util.h>
#include <msh/cli/runner.h>
#include <msh/log.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int	msh_resolve_fd(t_minishell *msh, const char *filename, char **name)
{
	int		fd;
	char	*resolved;

	if (name)
		*name = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		resolved = msh_resolve_path(msh, filename);
		if (resolved)
		{
			fd = open(resolved, O_RDONLY);
			if (fd >= 0 && name)
				*name = resolved;
			else
				free(resolved);
		}
	}
	else if (name)
		*name = ft_strdup((char *)filename);
	return (fd);
}

void	msh_run_file(
	t_minishell *msh,
	const char *file,
	int argc,
	const char **argv
) {
	char	*resolved;
	int		fd;
	int		ret;

	ret = 0;
	msh->execution_context.shell_args.argc = argc;
	msh->execution_context.shell_args.argv = argv;
	resolved = NULL;
	fd = msh_resolve_fd(msh, file, &resolved);
	if (fd < 0)
	{
		ft_dprintf(2, "%s: %s: %s\n", msh->name, file, strerror(errno));
		if (resolved)
			free(resolved);
		msh_exit(msh, 127);
	}
	if (msh_runner_check(msh, resolved, fd, &ret))
	{
		msh_run_setup_script(msh, msh_resolve_fd(msh, file, NULL), file);
		return ;
	}
	if (resolved)
		free(resolved);
	msh_exit(msh, ret);
}
