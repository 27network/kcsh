/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_reset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 22:48:42 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/09 14:25:50 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <shakespeare.h>
#include <stdio.h>
#include <unistd.h>

bool	shk_setup_cursor_base(t_shakespeare_data *shk)
{
	return (shk_cursor_pos_abs(shk, &shk->draw.cursor_base_x,
			&shk->draw.cursor_base_y));
}

bool	shk_reset(t_shakespeare_data *shk, const char *prompt, bool setup_term)
{
	if (setup_term && !shk_termios_setup(shk))
	{
		perror("shk_termios_setup");
		return (false);
	}
	if (shk->buffer)
		ft_strdel(&shk->buffer);
	shk->buffer = ft_calloc(SHK_BUFFER_BLOCK_SIZE, sizeof(char));
	if (!shk->buffer)
		return (false);
	if (!shk_setup_cursor_base(shk))
	{
		shk_termios_reset(shk);
		ft_strdel(&shk->buffer);
		return (false);
	}
	shk_window_update_size(shk);
	shk->history_current = NULL;
	shk->buffer_size = 0;
	shk->next_buffer_size = SHK_BUFFER_BLOCK_SIZE;
	shk->draw.prompt = prompt;
	shk->draw.cursor_pos = 0;
	shk->draw.old_draw_size = 0;
	return (true);
}
