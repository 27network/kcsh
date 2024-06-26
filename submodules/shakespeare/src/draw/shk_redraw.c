/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_redraw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 04:33:46 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/26 14:59:12 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <shakespeare.h>

void	shk_cursor_jump_abs(size_t x, size_t y);
void	shk_cursor_jump_logical(void);

void	shk_redraw(void)
{
	t_shakespeare_data	*shk;
	size_t				max_y;
	size_t				max_x;

	shk = shk_shared();
	max_x = shk->draw_ctx.cursor_base_x + shk_prompt_len(shk->draw_ctx.prompt)
		+ shk->buffer_size;
	max_y = shk->draw_ctx.cursor_base_y;
	while ((int)max_x > shk->draw_ctx.tty_cols)
	{
		max_x -= shk->draw_ctx.tty_cols;
		max_y++;
	}
	while (max_y > shk->draw_ctx.cursor_base_y)
	{
		shk_cursor_jump_abs(shk->draw_ctx.cursor_base_x, max_y);
		ft_putstr_fd("\033[2K\r", shk->draw_ctx.output_fd);
		max_y--;
	}
	shk_prompt_draw(shk->draw_ctx.prompt);
	ft_putstr_fd(shk->buffer, shk->draw_ctx.output_fd);
	shk_cursor_jump_logical();
	//TODO: cleanup after cursor(maybe print \0 as a space???? what about multi-editing)
	//TODO: backup last draw size
}
