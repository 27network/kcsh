/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shakespeare.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 05:37:56 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/09 14:26:38 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <ft/mem.h>
#include <ft/print.h>
#include <ft/string/parse.h>
#include <ft/string.h>
#include <shakespeare.h>
#include <stdio.h>
#include <unistd.h>

static void	shk_update_start(t_shakespeare_data *shk)
{
	size_t	height;

	height = shk_buffer_height(shk);
	if (height > 0)
		height--;
	if (!height)
		return ;
	if (shk->draw.cursor_base_y + height > (size_t) shk->draw.tty_rows)
		shk->draw.cursor_base_y--;
}

char	*shakespeare(const char *prompt)
{
	t_shakespeare_data	*shk;
	bool				running;

	shk = shk_shared();
	if (!shk_reset(shk, prompt, true))
		return (NULL);
	shk_redraw(shk);
	running = true;
	while (running)
	{
		ft_bzero(&shk->read_buffer, 2);
		if (-1 == read(STDIN_FILENO, &shk->read_buffer, 1) && errno != EAGAIN)
		{
			ft_strdel(&shk->buffer);
			break ;
		}
		running = shk_handle_char(shk, shk->read_buffer[0]);
		if (shk->hooks.input_hook)
			shk->hooks.input_hook(shk, SHK_HOOK_AFTER, shk->read_buffer[0],
				&running);
		shk_update_start(shk);
	}
	shk_termios_reset(shk);
	return (shk->buffer);
}
