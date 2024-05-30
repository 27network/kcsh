/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:43:26 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/30 18:37:16 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/minishell.h>
#include <msh/log.h>
#include <unistd.h>

int	msh_fork(t_minishell *msh)
{
	const int	pid = fork();

	if (pid == 0)
		msh->forked = true;
	msh_log(msh, MSG_DEBUG_GENERIC, "fork(); pid: %d\n", pid);
	return (pid);
}
