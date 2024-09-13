/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_history_modify_last.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:21:32 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/13 14:58:55 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <shakespeare.h>
#include <stdlib.h>

void	shk_history_push_entry(t_history_entry *entry);

void	shk_history_modify_last(const char *line)
{
	t_history_entry	*history;

	history = shk_history_pop();
	if (!history)
		return ;
	free(history->line);
	history->line = ft_strdup(line);
	if (!history->line)
	{
		free(history);
		return ;
	}
	shk_history_push_entry(history);
}

// See cli/src/history/msh_history_modify_last.c
void	msh_history_modify_last(const char *line)
		__attribute__((weak, alias("shk_history_modify_last")));
