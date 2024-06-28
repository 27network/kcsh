/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shakespeare.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 05:37:56 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/27 02:57:04 by kiroussa         ###   ########.fr       */
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

static void	shk_display_newlines(t_shakespeare_data *shk)
{
	size_t	size;
	size_t	cursor_y;

	shk_cursor_pos(shk, NULL, &cursor_y);
	cursor_y = cursor_y - shk->draw.cursor_base_y;
	size = shk_buffer_height(shk);
	while (size-- > cursor_y)
		ft_putstr_fd("\n", 1);
}

static bool	shk_handle_char(t_shakespeare_data *shk, char c)
{
	bool	ret;

	ret = true;
	if (shk->hooks.input_hook
		&& shk->hooks.input_hook(shk, SHK_HOOK_BEFORE, c, &ret))
		return (ret);
	if (c == 27)
		return (shk_handle_escape(shk));
	if (c == 4)
	{
		ft_strdel(&shk->buffer);
		(void) write(shk->draw.output_fd, "\r\n", 2);
		return (false);
	}
	if (c == '\r')
	{
		shk_buffer_append(shk, '\r');
		shk_display_newlines(shk);
		return (false);
	}
	if (c == 127)
		return (shk_cursor_backspace(shk, 1));
	if (c == '\t' || c == 0)
		return (true);
	return (shk_buffer_append(shk, c));
}

char	*shakespeare(const char *prompt)
{
	t_shakespeare_data	*shk;
	bool				running;

	shk = shk_shared();
	if (!shk_reset(shk, prompt))
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
	}
	shk_termios_reset(shk);
	return (shk->buffer);
}
