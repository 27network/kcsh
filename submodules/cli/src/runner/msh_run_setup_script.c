/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_run_setup_script.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 03:06:45 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/04 11:50:34 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <msh/env.h>
#include <msh/features.h>
#include <msh/log.h>
#include <msh/cli/runner.h>
#include <stdlib.h>
#include <unistd.h>

#if FEAT_SCRIPTING

void	msh_run_setup_script(t_minishell *msh, int fd, const char *filename)
{
	const char	*env = msh_env_value(msh, "MSH_DISABLE_SCRIPT_WARNING");

	if (!env || !*env)
		msh_error(msh, "warning: the script runner is very much WIP, bugs will"
			" arise.\nrun with MSH_DISABLE_SCRIPT_WARNING=1 to disable this"
			" message.\n");
	msh->execution_context.file = fd;
	msh->execution_context.filename = filename;
	msh->execution_context.show_line = true;
	msh->interactive = false;
}

#else

void	msh_run_setup_script(t_minishell *msh, int fd, const char *filename)
{
	msh_error(msh, "%s: running scripts isn't supported.\n", filename);
	if (fd >= 0)
		close(fd);
	if (msh->name)
		free((char *) msh->name);
	msh_exit(msh, 121);
}

#endif // FEAT_SCRIPTING
