/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_cursor_jump_abs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:43:54 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/26 14:44:00 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <shakespeare.h>

void	shk_cursor_jump_abs(size_t x, size_t y)
{
	ft_dprintf(shk_shared()->draw_ctx.output_fd, "\033[%d;%dH", y, x);
}
