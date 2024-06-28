/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_history_modify_last.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:51:58 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/28 22:18:49 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/features.h>
#include <msh/cli/history.h>
#if !FEAT_NO_READLINE
# include <ft/string.h>
# include <stdlib.h>

void	msh_history_modify_last(const char *line)
{
	HIST_ENTRY	***ptr;
	HIST_ENTRY	**history;
	HIST_ENTRY	*entry;
	size_t		i;

	if (!line || !*line)
		return ;
	ptr = msh_history_raw();
	if (!ptr || !*ptr)
		return ;
	history = *ptr;
	i = 0;
	while (history[i])
		i++;
	if (i == 0)
	{
		msh_history_push(line);
		return ;
	}
	entry = history[i - 1];
	free(entry->line);
	entry->line = ft_strdup(line);
}

#else

/**
 * Wow. Such code. Much history. So empty. Wow.
 *
 * You know you have a good codebase when you can pull stuff like this and it
 * makes perfect logical sense.
 *
 * And yes, i'm proud of this.
 */

#endif // !FEAT_NO_READLINE
