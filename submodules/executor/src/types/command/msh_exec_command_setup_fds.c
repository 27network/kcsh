/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_command_setup_fds.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 19:31:40 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/30 10:03:59 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/data/list.h>
#include <msh/exec.h>
#include <msh/log.h>
#include <unistd.h>

/**
 * @brief	Sets up the forks' base redirection (stdin) from
 * 			the `fd_stack`, but also from the `fds` `pipe`'d array
 *
 * @param	state	The current state
 * @param	fds		The pipe'd array of fds
 *
 * @return	0 on success, 1 on failure
 */
// int	msh_exec_command_setup_fds(t_exec_state *state, int fds[2])
// {
// 	int		ret;
// 	t_list	*fd_list;
//
// 	if (state->fd_stack)
// 	{
// 		fd_list = ft_lst_last(state->fd_stack);
// 		ret = (int)(uint64_t)fd_list->content;
// 		ft_lst_remove(&state->fd_stack, fd_list, NULL);
// 		if (dup2(ret, STDIN_FILENO) == -1)
// 		{
// 			msh_error(state->msh, "failed to setup stdin\n");
// 			close(ret);
// 			return (1);
// 		}
// 		close(ret);
// 	}
// 	if (dup2(fds[1], STDOUT_FILENO) == -1)
// 	{
// 		msh_error(state->msh, "failed to setup stdin\n");
// 		close(fds[1]);
// 		return (1);
// 	}
// 	return (close(fds[1]));
// }

int	msh_save_fds(t_minishell *msh, int fds[3])
{
	int		ret;

	(void) msh;
	ret = dup(STDOUT_FILENO);
	if (ret == -1)
		return (0);
	fds[0] = ret;
	ret = dup(STDERR_FILENO);
	if (ret == -1)
	{
		close(fds[0]);
		return (0);
	}
	fds[1] = ret;
	ret = dup(STDIN_FILENO);
	if (ret == -1)
	{
		close(fds[0]);
		close(fds[1]);
		return (0);
	}
	fds[2] = ret;
	return (1);
}

int	msh_restore_fds(t_minishell *msh, int fds[3])
{
	int		ret;

	(void) msh;
	ret = dup2(fds[0], STDOUT_FILENO);
	close(fds[0]);
	if (ret == -1)
	{
		close(fds[1]);
		close(fds[2]);
		return (0);
	}
	ret = dup2(fds[1], STDERR_FILENO);
	close(fds[1]);
	if (ret == -1)
		close(fds[2]);
	if (ret == -1)
		return (0);
	ret = dup2(fds[2], STDIN_FILENO);
	close(fds[2]);
	if (ret == -1)
		return (0);
	return (1);
}
