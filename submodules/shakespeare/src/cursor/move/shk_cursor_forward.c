/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_cursor_forward.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 04:48:34 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/27 01:25:38 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <ft/print.h>
#include <shakespeare.h>

void	shk_cursor_forward(t_shakespeare_data *shk, int n)
{
	n = ft_min(n, shk->buffer_size);
	if (n <= 0)
		return ;
	shk->draw.cursor_pos += n;
	shk_cursor_jump_logical(shk);
}
