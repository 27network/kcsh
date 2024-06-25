/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_cursor_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 06:59:45 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/25 07:09:45 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shakespeare.h>

#include <stdio.h>

void	shk_cursor_pos(t_shakespeare_data *shk, size_t *x, size_t *y)
{
	size_t	cursor;
	size_t	prompt_len;
	int		base_x;
	size_t	base_y;

	cursor = shk->draw_ctx.cursor_pos;
	prompt_len = shk_prompt_len(shk->draw_ctx.prompt);
	base_x = shk->draw_ctx.cursor_base_x;
	base_y = shk->draw_ctx.cursor_base_y;
	base_x += prompt_len;
	base_x += cursor;
	while (shk->draw_ctx.tty_cols && base_x >= shk->draw_ctx.tty_cols)
	{
		base_x -= shk->draw_ctx.tty_cols;
		base_y++;
	}
	if (x)
		*x = base_x;
	if (y)
		*y = base_y;
}
