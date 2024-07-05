/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_history_prev.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:06:41 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/02 19:09:27 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shakespeare.h>

void	shk_history_prev(t_shakespeare_data *shk)
{
	if (!shk->history_stack)
		return ;
	if (!shk->history_current)
		shk->history_current = shk->history_stack;
	else if (shk->history_current->prev)
		shk->history_current = shk->history_current->prev;
}
