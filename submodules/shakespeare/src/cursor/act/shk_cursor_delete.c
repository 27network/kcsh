/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_cursor_delete.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 06:39:51 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/27 01:50:53 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <shakespeare.h>

bool	shk_cursor_delete(t_shakespeare_data *shk, int n)
{
	size_t	i;

	n = ft_min(shk->buffer_size, n);
	if (n <= 0)
		return (true);
	while (n-- > 0)
	{
		i = shk->draw.cursor_pos;
		while (shk->buffer[i] && i < shk->buffer_size)
		{
			shk->buffer[i] = shk->buffer[i + 1];
			i++;
		}
		shk->buffer[i] = '\0';
		shk->buffer_size--;
	}
	shk_redraw(shk);
	return (true);
}
