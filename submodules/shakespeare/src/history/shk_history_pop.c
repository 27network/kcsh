/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_history_pop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 06:39:57 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/23 06:46:06 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shakespeare.h>

t_history_entry	*shk_history_pop(void)
{
	t_shakespeare_data	*shk;
	t_history_entry		*tmp;

	shk = shk_shared();
	if (!shk->history_stack)
		return (NULL);
	tmp = shk->history_stack;
	shk->history_stack = shk->history_stack->next;
	if (shk->history_stack)
		shk->history_stack->prev = NULL;
	return (tmp);
}
