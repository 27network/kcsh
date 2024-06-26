/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_cursor_backward.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 04:50:43 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/26 14:50:57 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <shakespeare.h>

void	shk_cursor_backward(int n)
{
	t_shakespeare_data	*shk;
	char				*backspace;
	int					i;
	size_t				cursor_x;
	size_t				cursor_y;

	shk = shk_shared();
	if ((int)shk->draw_ctx.cursor_pos - n < 0)
		n = shk->draw_ctx.cursor_pos;
	if (n <= 0)
		return ;
	backspace = shk->draw_ctx.backspace;
	if (!backspace)
		backspace = "\b";
	i = 0;
	while (i < n)
	{
		shk_cursor_pos(shk, &cursor_x, &cursor_y);
		if (cursor_x == 1)
			shk_cursor_jump_abs(shk->draw_ctx.tty_cols, cursor_y - 1);
		else
			ft_putstr_fd(backspace, shk->draw_ctx.output_fd);
		shk->draw_ctx.cursor_pos--;
		i++;
	}
}
