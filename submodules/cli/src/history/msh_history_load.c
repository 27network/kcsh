/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_history_load.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:31:55 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/10 17:07:19 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/features.h>
#include <msh/cli/history.h>
#if FEAT_HISTORY_FILE
# include <fcntl.h>
# include <ft/io.h>
# include <ft/string.h>
# include <msh/log.h>
# include <stdlib.h>
# include <unistd.h>

static void	msh_history_push_nonewline(t_minishell *msh, char *line, int i)
{
	size_t	size;

	if (!line || !*line)
		return ;
	size = ft_strlen(line);
	if (size && line[size - 1] == '\n')
		line[size - 1] = '\0';
	msh_log(msh, MSG_DEBUG_GENERIC, "history[%d] = \"%s\"\n", (int)i, line);
	msh_history_push(line);
}

void	msh_history_load(t_minishell *msh)
{
	const int	fd = msh_history_file(msh, O_RDONLY);
	char		*line;
	int			i;

	if (fd < 0)
		return ;
	i = 0;
	msh_log(msh, MSG_DEBUG_GENERIC, "loading history from file\n");
	while (!msh->forked)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		msh_history_push_nonewline(msh, line, i++);
		free(line);
	}
	close(fd);
	msh_log(msh, MSG_DEBUG_GENERIC, "loaded %d lines from history file\n", i);
}

#else

void	msh_history_load([[maybe_unused]] t_minishell *msh)
{
}

#endif // FEAT_HISTORY_FILE
