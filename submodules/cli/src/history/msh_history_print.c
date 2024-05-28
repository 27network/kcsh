/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_history_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 21:01:25 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/28 21:24:27 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/cli/history.h>
#include <stdio.h>

void	msh_history_print(void)
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
	{
		printf("HIST_ENTRY { line=\"%s\", timestamp=\"%s\", data=\"%p\" }\n",
			history[i]->line, history[i]->timestamp, history[i]->data);
		i++;
	}
}
