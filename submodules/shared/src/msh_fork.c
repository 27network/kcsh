/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:43:26 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/30 03:58:24 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/minishell.h>
#include <msh/log.h>
#include <unistd.h>

int	msh_fork(t_minishell *msh)
{
	const int	pid = fork();

	if (pid == 0)
		msh->forked++;
	msh_debug(msh, "fork(%d); pid: %d\n", (int)msh->forked, pid);
	return (pid);
}
