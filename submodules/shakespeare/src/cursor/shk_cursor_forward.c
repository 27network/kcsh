/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_cursor_forward.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 04:48:34 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/25 06:21:31 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <shakespeare.h>

void	shk_cursor_forward(int n)
{
	t_shakespeare_data	*shk;
	size_t				max_len;

	shk = shk_shared();
	max_len = shk->buffer_size;
	if (shk->draw_ctx.cursor_pos + n > max_len)
		n = max_len - shk->draw_ctx.cursor_pos;
	if (n <= 0)
		return ;
	shk->draw_ctx.cursor_pos += n;
	ft_dprintf(shk->draw_ctx.output_fd, "\033[%dC", n);
}
