/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_history_first.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:10:33 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/02 19:10:55 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shakespeare.h>

void	shk_history_first(t_shakespeare_data *shk)
{
	if (!shk->history_stack)
		return ;
	shk->history_current = shk->history_stack;
	while (shk->history_current->prev)
		shk->history_current = shk->history_current->prev;
}
