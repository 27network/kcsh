/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_buffer_height.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:25:28 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/26 18:19:44 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shakespeare.h>

size_t	shk_buffer_height(t_shakespeare_data *shk)
{
	size_t	cursor_x;
	size_t	cursor_y;

	shk_cursor_pos(shk, &cursor_x, &cursor_y);
	return ((cursor_y - shk->draw.cursor_base_y) + 1);
}
