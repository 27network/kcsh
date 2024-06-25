/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_redraw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 04:33:46 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/25 18:22:08 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <shakespeare.h>

void	shk_redraw(void)
{
	t_shakespeare_data	*shk;
	size_t				cursor_x;
	size_t				cursor_y;

	shk = shk_shared();
	ft_putstr_fd("\033[2K\r", shk->draw_ctx.output_fd);
	shk_prompt_draw(shk->draw_ctx.prompt);
	ft_putstr_fd(shk->buffer, shk->draw_ctx.output_fd);
	shk_cursor_pos(shk, &cursor_x, &cursor_y);
	ft_dprintf(shk->draw_ctx.output_fd, "\033[%d;%dH",
		(int) cursor_y, (int) cursor_x);
}
