/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_handle_escape.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 06:30:15 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/02 18:51:13 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string/parse.h>
#include <ft/string.h>
#include <shakespeare.h>
#include <unistd.h>

#include <stdio.h>

static bool	shk_goto_history_ends(t_shakespeare_data *shk, int mod)
{
	(void) shk;
	(void) mod;
	return (true);
}

static bool	shk_cursor_jump_ends(t_shakespeare_data *shk, char cmd)
{
	if (cmd == 'F')
		shk_cursor_jump_end(shk);
	else if (cmd == 'H')
		shk_cursor_jump_start(shk);
	return (true);
}

static bool	shk_handle_escape_modifier(
	t_shakespeare_data *shk,
	int modifier,
	char *bufptr
) {
	const char	cmd = *bufptr;

	(void) modifier;
	if (cmd == 'C')
		shk_cursor_forward(shk, 1);
	else if (cmd == 'D')
		shk_cursor_backward(shk, 1);
	else if (cmd == 'A')
		(void)shk; // hist up
	else if (cmd == 'B')
		(void)shk; // hist down
	else if (cmd == '~' && modifier == 3)
		return (shk_cursor_delete(shk, 1));
	else if (cmd == '~')
		return (shk_goto_history_ends(shk, modifier));
	else if (cmd == 'F' || cmd == 'H')
		return (shk_cursor_jump_ends(shk, cmd));
	return (true);
}

bool	shk_handle_escape(t_shakespeare_data *shk)
{
	char	buf[64];
	int		modifier;
	char	*bufptr;

	ft_bzero(buf, 64);
	if (read(0, buf, 64) == -1)
		return (false);
	bufptr = buf;
	if (*bufptr == '[')
	{
		bufptr++;
		modifier = 0;
		if (ft_strchr(bufptr, ';'))
			bufptr = ft_strchr(bufptr, ';') + 1;
		modifier = ft_atoi(bufptr);
		if (modifier != 0)
			bufptr += ft_lllen(modifier);
		return (shk_handle_escape_modifier(shk, modifier, bufptr));
	}
	return (true);
}
