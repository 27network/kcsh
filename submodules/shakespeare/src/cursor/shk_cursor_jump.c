/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_cursor_jump.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 07:20:50 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/25 07:36:53 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <shakespeare.h>

#include <stdio.h>

void	shk_cursor_jump(t_shakespeare_data *shk, size_t x, size_t y)
{
	size_t	cursor_x;
	size_t	cursor_y;
	size_t	diff_x;
	size_t	diff_y;

	shk_cursor_pos(shk, &cursor_x, &cursor_y);
	if (x < shk->draw_ctx.cursor_base_x)
		x = shk->draw_ctx.cursor_base_x;
	if (y < shk->draw_ctx.cursor_base_y)
		y = shk->draw_ctx.cursor_base_y;
	if ((int)x > shk->draw_ctx.tty_cols)
		x = shk->draw_ctx.tty_cols;
	if ((int)y > shk->draw_ctx.tty_rows)
		y = shk->draw_ctx.tty_rows;
	diff_x = x - cursor_x;
	diff_y = y - cursor_y;
	shk->draw_ctx.cursor_pos -= diff_y * shk->draw_ctx.tty_cols + diff_x;
	ft_dprintf(shk->draw_ctx.output_fd, "\033[%d;%dH", y, x);
}
