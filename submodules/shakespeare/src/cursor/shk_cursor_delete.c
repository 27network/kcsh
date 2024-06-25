/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_cursor_delete.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 06:39:51 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/25 17:21:28 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shakespeare.h>

bool	shk_cursor_delete(t_shakespeare_data *shk)
{
	size_t	i;

	i = shk->draw_ctx.cursor_pos;
	while (shk->buffer[i])
	{
		shk->buffer[i] = shk->buffer[i + 1];
		i++;
	}
	shk->buffer_size--;
	shk_redraw();
	return (true);
}
