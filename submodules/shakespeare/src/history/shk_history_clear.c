/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_history_clear.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 06:40:27 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/23 06:46:06 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shakespeare.h>
#include <stdlib.h>

void	shk_history_clear(void)
{
	t_history_entry	*entry;

	while (1)
	{
		entry = shk_history_pop();
		if (!entry)
			break ;
		free(entry->line);
		free(entry);
	}
}
