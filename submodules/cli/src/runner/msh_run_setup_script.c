/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_run_setup_script.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 03:06:45 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/18 03:37:11 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <msh/env.h>
#include <msh/cli/runner.h>

#define UNSTABLE_SCRIPT_RUNNER 1

void	msh_run_setup_script(t_minishell *msh, int fd, const char *filename)
{
	char	*env;

	if (!UNSTABLE_SCRIPT_RUNNER)
	{
		msh_error(msh, "%s: running scripts isn't supported.\n", filename);
		return ;
	}
	env = msh_env_get(msh, "MSH_DISABLE_SCRIPT_WARNING");
	if (!env || !*env)
		msh_error(msh, "warning: the script runner is very much WIP, bugs will"
			" arise.\nrun with MSH_DISABLE_SCRIPT_WARNING=1 to disable this"
			" message.\n");
	msh->execution_context.file = fd;
	msh->execution_context.filename = filename;
	msh->execution_context.show_line = true;
	msh->interactive = false;
}
