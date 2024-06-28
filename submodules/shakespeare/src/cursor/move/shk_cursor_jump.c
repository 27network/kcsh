/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_cursor_jump.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 07:20:50 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/26 17:32:30 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <shakespeare.h>

void	shk_cursor_jump(t_shakespeare_data *shk, size_t x, size_t y)
{
	size_t	cursor_x;
	size_t	cursor_y;
	int		diff_x;
	int		diff_y;

	shk_cursor_pos(shk, &cursor_x, &cursor_y);
	if (x < shk->draw.cursor_base_x)
		x = shk->draw.cursor_base_x;
	if (y < shk->draw.cursor_base_y)
		y = shk->draw.cursor_base_y;
	if ((int)x > shk->draw.tty_cols)
		x = shk->draw.tty_cols;
	if ((int)y > shk->draw.tty_rows)
		y = shk->draw.tty_rows;
	diff_x = cursor_x - x;
	diff_y = cursor_y - y;
	shk->draw.cursor_pos -= diff_y * shk->draw.tty_cols + diff_x;
	shk_cursor_jump_abs(shk, x, y);
}
