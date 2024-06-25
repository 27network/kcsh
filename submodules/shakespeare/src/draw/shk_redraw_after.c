/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_redraw_after.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 04:43:46 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/25 06:59:42 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <shakespeare.h>

__attribute__((unused))
static void	shk_clear_line(void)
{
	ft_putstr_fd("\033[2K", 1);
}

void	shk_redraw_after(void)
{
	t_shakespeare_data	*shk;
	size_t				cursor;
	size_t				max_len;
	size_t				cursor_x;
	size_t				cursor_y;

	shk = shk_shared();
	cursor = shk->draw_ctx.cursor_pos;
	max_len = shk->buffer_size;
	if (cursor == max_len)
	{
		shk_cursor_forward(1);
		ft_putstr_fd(" ", shk->draw_ctx.output_fd);
		shk_cursor_backward(1);
		return ;
	}
	shk_cursor_pos(shk, &cursor_x, &cursor_y);
}
