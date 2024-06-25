/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_cursor_backspace.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 06:39:40 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/25 07:09:31 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shakespeare.h>

#include <stdio.h>

bool	shk_cursor_backspace(t_shakespeare_data *shk)
{
	if (shk->draw_ctx.cursor_pos > 0)
	{
		shk_cursor_backward(1);
		return (shk_cursor_delete(shk));
	}
	return (true);
}
