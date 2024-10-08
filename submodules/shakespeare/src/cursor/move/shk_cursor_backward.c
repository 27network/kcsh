/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_cursor_backward.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 04:50:43 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/27 01:24:48 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <ft/print.h>
#include <shakespeare.h>

void	shk_cursor_backward(t_shakespeare_data *shk, int n)
{
	n = ft_min(shk->draw.cursor_pos, n);
	if (n <= 0)
		return ;
	shk->draw.cursor_pos -= n;
	shk_cursor_jump_logical(shk);
}
