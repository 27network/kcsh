/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_handle_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:23:04 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/02 16:42:44 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <ft/string.h>
#include <shakespeare.h>
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

static bool	shk_handle_ctrl_char(t_shakespeare_data *shk, char c)
{
	if (c == 127)
		return (shk_cursor_backspace(shk, 1));
	if (c == 27)
		return (shk_handle_escape(shk));
	if (c == 4 && !shk->buffer[0])
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
	return (true);
}

bool	shk_handle_char(t_shakespeare_data *shk, char c)
{
	bool	ret;

	ret = true;
	if (shk->hooks.input_hook
		&& shk->hooks.input_hook(shk, SHK_HOOK_BEFORE, c, &ret))
		return (ret);
	if (ft_iscntrl(c))
		return (shk_handle_ctrl_char(shk, c));
	return (shk_buffer_append(shk, c));
}
