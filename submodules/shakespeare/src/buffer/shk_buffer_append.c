/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_buffer_append.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:02:31 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/16 14:27:51 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/print.h>
#include <shakespeare.h>
#include <unistd.h>

static bool	shk_handle_insertion(t_shakespeare_data *shk)
{
	const bool	has_insert = shk->buffer[shk->draw.cursor_pos] != '\0';
	int			i;

	if (has_insert)
	{
		i = shk->buffer_size;
		while (i > 0 && i > shk->draw.cursor_pos)
		{
			shk->buffer[i] = shk->buffer[i - 1];
			i--;
		}
	}
	return (has_insert);
}

static bool	shk_buffer_grow(t_shakespeare_data *shk)
{
	if (shk->buffer_size >= shk->next_buffer_size - 2)
	{
		shk->next_buffer_size = shk->buffer_size + SHK_BUFFER_BLOCK_SIZE;
		shk->buffer = ft_realloc(shk->buffer, shk->buffer_size,
				shk->next_buffer_size);
	}
	return (shk->buffer != NULL);
}

static void	shk_edge_cursor(t_shakespeare_data *shk)
{
	size_t	cursor_x;

	shk_cursor_pos(shk, &cursor_x, NULL);
	if ((int)cursor_x == 1)
		ft_printf("\n");
}

bool	shk_buffer_append(t_shakespeare_data *shk, char c)
{
	char	insert_str[5];
	bool	insert;

	if (c == '\0' || c == '\r')
		return (false);
	insert = shk_handle_insertion(shk);
	shk->buffer[shk->draw.cursor_pos++] = c;
	shk->buffer_size++;
	shk->draw.old_draw_size = shk->buffer_size;
	if (insert)
	{
		ft_memcpy(insert_str, "\033[1@ ", 5);
		insert_str[4] = c;
		(void) !write(shk->draw.output_fd, insert_str, 5);
	}
	else
		(void) !write(shk->draw.output_fd, &c, 1);
	if (!insert)
		shk_edge_cursor(shk);
	else
		shk_redraw(shk);
	return (shk_buffer_grow(shk));
}
