/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_cursor_forward.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 04:48:34 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/02 14:11:18 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <ft/print.h>
#include <shakespeare.h>

void	shk_cursor_forward(t_shakespeare_data *shk, int n)
{
	if (shk->draw.cursor_pos + n > (int) shk->buffer_size)
		n = shk->buffer_size - shk->draw.cursor_pos;
	shk->draw.cursor_pos += n;
	shk_cursor_jump_logical(shk);
}
