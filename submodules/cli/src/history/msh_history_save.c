/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_history_save.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:32:03 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/28 23:50:19 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <msh/cli/history.h>
#include <msh/log.h>
#include <fcntl.h>
#include <unistd.h>

void	msh_history_save(t_minishell *msh)
{
	HIST_ENTRY	***history_ptr;
	HIST_ENTRY	**history;
	int			i;
	int			fd;

	if (!msh->interactive)
		return ;
	history_ptr = msh_history_raw();
	if (!history_ptr || !*history_ptr)
		return ;
	fd = msh_history_file(msh, O_CREAT | O_TRUNC | O_WRONLY);
	if (fd < 0)
		return ;
	history = *history_ptr;
	i = 0;
	while (history[i])
	{
		if (ft_dprintf(fd, "%s\n", history[i]->line) <= 0)
			break ;
		i++;
	}
	close(fd);
}
