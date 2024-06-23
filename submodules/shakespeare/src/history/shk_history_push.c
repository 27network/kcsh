/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_history_push.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 06:38:19 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/23 06:46:06 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <shakespeare.h>
#include <stdlib.h>

void	shk_history_push(const char *line)
{
	t_shakespeare_data	*shk;
	t_history_entry		*new;

	shk = shk_shared();
	new = ft_calloc(1, sizeof(t_history_entry));
	if (!new)
		return ;
	new->line = ft_strdup(line);
	if (!new->line)
	{
		free(new);
		return ;
	}
	if (shk->history_stack)
		shk->history_stack->prev = new;
	new->next = shk->history_stack;
	shk->history_stack = new;
}
