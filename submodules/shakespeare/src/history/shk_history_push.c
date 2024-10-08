/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_history_push.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 06:38:19 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/28 20:25:18 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <shakespeare.h>
#include <stdlib.h>

void	shk_history_push_entry(t_history_entry *new)
{
	t_shakespeare_data	*shk;

	if (!new)
		return ;
	shk = shk_shared();
	if (shk->history_stack)
		shk->history_stack->prev = new;
	new->next = shk->history_stack;
	shk->history_stack = new;
}

void	shk_history_push(const char *line)
{
	t_history_entry		*new;

	new = ft_calloc(1, sizeof(t_history_entry));
	if (!new)
		return ;
	new->line = ft_strdup(line);
	if (!new->line)
	{
		free(new);
		return ;
	}
	shk_history_push_entry(new);
}
