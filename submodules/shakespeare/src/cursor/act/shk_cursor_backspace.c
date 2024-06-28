/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_cursor_backspace.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 06:39:40 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/27 01:23:08 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <shakespeare.h>

bool	shk_cursor_backspace(t_shakespeare_data *shk, int n)
{
	n = ft_min(shk->draw.cursor_pos, n);
	shk_cursor_backward(shk, n);
	return (shk_cursor_delete(shk, n));
}
