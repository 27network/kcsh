/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_history_load.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:31:55 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/29 23:58:44 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <ft/io.h>
#include <ft/string.h>
#include <msh/cli/history.h>
#include <msh/log.h>
#include <stdlib.h>
#include <unistd.h>

static void	msh_history_push_nonewline(char *line)
{
	size_t	size;

	if (!line || !*line)
		return ;
	size = ft_strlen(line);
	if (size && line[size - 1] == '\n')
		line[size - 1] = '\0';
	msh_history_push(line);
}

void	msh_history_load(t_minishell *msh)
{
	const int	fd = msh_history_file(msh, O_RDONLY);
	char		*line;

	if (fd < 0)
		return ;
	while (!msh->forked)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		msh_history_push_nonewline(line);
		free(line);
	}
	close(fd);
	msh_log(msh, MSG_DEBUG_GENERIC, "loaded history from file successfully\n");
}
