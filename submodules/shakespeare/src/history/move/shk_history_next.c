/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_history_next.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:09:51 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/02 19:10:13 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shakespeare.h>

void	shk_history_next(t_shakespeare_data *shk)
{
	if (!shk->history_stack)
		return ;
	if (shk->history_current && shk->history_current->next)
		shk->history_current = shk->history_current->next;
}
