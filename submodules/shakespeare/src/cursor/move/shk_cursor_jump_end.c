/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_cursor_jump_end.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 07:20:20 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/26 17:32:31 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <shakespeare.h>

void	shk_cursor_jump_end(t_shakespeare_data *shk)
{
	size_t	x;
	size_t	y;

	x = shk->draw.cursor_base_x;
	y = shk->draw.cursor_base_y;
	x += shk_prompt_len(shk->draw.prompt);
	x += shk->buffer_size;
	while ((int) x > shk->draw.tty_cols)
	{
		x -= shk->draw.tty_cols;
		y++;
	}
	shk_cursor_jump(shk, x, y);
}
