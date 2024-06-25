/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_cursor_backward.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 04:50:43 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/25 07:10:57 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <shakespeare.h>

#include <stdio.h>

void	shk_cursor_backward(int n)
{
	t_shakespeare_data	*shk;
	char				*backspace;

	shk = shk_shared();
	if ((int)shk->draw_ctx.cursor_pos - n < 0)
		n = shk->draw_ctx.cursor_pos;
	if (n <= 0)
		return ;
	backspace = shk->draw_ctx.backspace;
	if (!backspace)
		backspace = "\b";
	// printf("BK%d(%d)\n", n, shk->draw_ctx.cursor_pos);
	shk->draw_ctx.cursor_pos -= n;
	while (n-- > 0)
		ft_putstr_fd(backspace, shk->draw_ctx.output_fd);
}
