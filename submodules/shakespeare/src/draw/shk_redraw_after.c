/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_redraw_after.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 04:43:46 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/26 17:33:23 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <shakespeare.h>

__attribute__((unused))
static void	shk_clear_line(void)
{
	ft_putstr_fd("\033[2K", 1);
}

void	shk_redraw_after(t_shakespeare_data *shk)
{
	size_t				cursor;
	size_t				max_len;
	size_t				cursor_x;
	size_t				cursor_y;

	cursor = shk->draw.cursor_pos;
	max_len = shk->buffer_size;
	if (cursor == max_len)
	{
		shk_cursor_forward(shk, 1);
		ft_putstr_fd(" ", shk->draw.output_fd);
		shk_cursor_backward(shk, 1);
		return ;
	}
	shk_cursor_pos(shk, &cursor_x, &cursor_y);
}
