/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_window_update_size.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 22:54:55 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/28 14:27:03 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <shakespeare.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#ifdef TIOCGWINSZ

static int	shk_wrap_ioctl(struct winsize *ws)
{
	return (ioctl(STDIN_FILENO, TIOCGWINSZ, ws));
}

#else

static int	shk_wrap_ioctl([[maybe_unused]] struct winsize *ws)
{
	return (-1);
}

#endif // TIOCGWINSZ

static void	shk_window_fallback_update(t_shakespeare_data *shk)
{
	size_t	old_x;
	size_t	old_y;
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	shk_cursor_pos(shk, &old_x, &old_y);
	shk_cursor_jump_abs(shk, 99999, 99999);
	if (!shk_cursor_pos_abs(shk, &x, &y))
		return ;
	shk_cursor_jump_abs(shk, old_x, old_y);
	if (x < 1)
		x = 80;
	if (y < 1)
		y = 24;
	shk->draw.tty_cols = x;
	shk->draw.tty_rows = y;
}

void	shk_window_update_size(t_shakespeare_data *shk)
{
	struct winsize	ws;

	shk->draw.tty_cols = -1;
	shk->draw.tty_rows = -1;
	ft_bzero(&ws, sizeof(ws));
	if (shk_wrap_ioctl(&ws) == -1)
		shk_window_fallback_update(shk);
	else
	{
		if (ws.ws_col < 1)
			ws.ws_col = 80;
		if (ws.ws_row < 1)
			ws.ws_row = 24;
		shk->draw.tty_cols = ws.ws_col;
		shk->draw.tty_rows = ws.ws_row;
	}
}
