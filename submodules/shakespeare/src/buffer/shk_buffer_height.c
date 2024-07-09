/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_buffer_height.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:25:28 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/09 17:27:11 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shakespeare.h>

/**
 * @note This is more of a height diff for the final buffer print before
 * returning to the consumer
 */
size_t	shk_buffer_height(t_shakespeare_data *shk)
{
	size_t	max_height;
	int		save;

	save = shk->draw.cursor_pos;
	shk->draw.cursor_pos = shk->buffer_size;
	shk_cursor_pos(shk, NULL, &max_height);
	shk->draw.cursor_pos = save;
	max_height -= shk->draw.cursor_base_y;
	return (max_height + 1);
}
