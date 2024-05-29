/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_history_pop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:09:19 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/29 03:27:07 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/cli/history.h>
#include <stdlib.h>

void	msh_history_pop(void)
{
	HIST_ENTRY	***ptr;
	HIST_ENTRY	**history;
	int			i;

	ptr = msh_history_raw();
	if (!ptr || !*ptr)
		return ;
	history = *ptr;
	i = 0;
	while (history[i])
		i++;
	if (i > 0)
	{
		if (history[i - 1]->line)
			free(history[i - 1]->line);
		free(history[i - 1]);
		history[i - 1] = NULL;
	}
}
