/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_run_script.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 03:06:45 by kiroussa          #+#    #+#             */
/*   Updated: 2024/04/10 19:38:25 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <msh/minishell.h>
#include <msh/cli/runner.h>

void	msh_runner_error_handler(void *msh, const char *msg);

int	msh_run_script(t_minishell *msh, int fd, const char *filename)
{
	msh->name = msh->binary_name;
	msh_error(msh, "%s: running scripts isn't supported.\n", filename);
	msh->error_handler = &msh_runner_error_handler;
	(void)fd;
	return (121);
}
