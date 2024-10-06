/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_command_not_found.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 05:35:21 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/05 04:45:37 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/log.h>
#include <msh/util.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define COMMAND_NOT_FOUND "command-not-found"

char	*msh_resolve_path_internal(t_minishell *msh, const char *filename);

static bool	msh_command_not_found_invoke(t_minishell *msh, char *name,
				char *binary)
{
	pid_t	pid;
	int		status;

	pid = msh_fork(msh);
	if (pid == -1)
		return (false);
	if (pid == 0)
	{
		execve(binary, (char *[]){binary, name, NULL}, NULL);
		free(binary);
		msh_exit(msh, 1);
		return (false);
	}
	waitpid(pid, &status, 0);
	free(binary);
	return (true);
}

void	msh_command_not_found(t_minishell *msh, const char *name)
{
	char	*binary;

	if (msh->execution_context.show_line)
	{
		msh_error(msh, "%s: command not found\n", name);
		return ;
	}
	binary = msh_resolve_path_internal(msh, COMMAND_NOT_FOUND);
	if (!binary || !msh_command_not_found_invoke(msh, (char *)name, binary))
		msh_error(msh, "%s: command not found\n", name);
}
