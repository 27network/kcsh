/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_cursor_delete.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 06:39:51 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/26 14:44:55 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shakespeare.h>

#include <stdio.h>

bool	shk_cursor_delete(t_shakespeare_data *shk)
{
	size_t	i;

	i = shk->draw_ctx.cursor_pos;
	// printf("\r\nbuffer before: %s\n", shk->buffer);
	// printf("buffer_size before: %zu\n", shk->buffer_size);
	while (shk->buffer[i] && i < shk->buffer_size - 1)
	{
		shk->buffer[i] = shk->buffer[i + 1];
		i++;
	}
	shk->buffer[i] = '\0';
	shk->buffer_size--;
	// printf("buffer after: %s\n", shk->buffer);
	// printf("buffer_size after: %zu\n", shk->buffer_size);
	shk_redraw();
	return (true);
}
