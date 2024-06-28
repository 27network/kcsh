/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_cursor_pos_abs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:39:19 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/27 16:55:02 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string/parse.h>
#include <ft/string.h>
#include <shakespeare.h>
#include <stdio.h>
#include <unistd.h>

static bool	shk_cursor_read_escape(char *buf, size_t *x, size_t *y)
{
	char	*first;

	first = ft_strdup_range(buf, 1, ft_strchr(buf, ';') - buf);
	if (!first)
	{
		perror("strdup_range");
		return (false);
	}
	if (y)
		*y = ft_atoi(first);
	free(first);
	while (*buf && *buf != ';')
		buf++;
	if (*buf)
		buf++;
	else
		return (false);
	if (x)
		*x = ft_atoi(buf);
	return (true);
}

bool	shk_cursor_pos_abs(t_shakespeare_data *shk, size_t *x, size_t *y)
{
	char	buf_write[33];
	char	*buf;

	(void) shk;
	if (!x && !y)
		return (true);
	if (write(1, "\033[6n", 4) != 4)
		return (false);
	buf = buf_write;
	ft_bzero(buf_write, 33);
	if (read(0, buf_write, 32) <= 0)
		return (false);
	while (*buf && *buf != '[')
		buf++;
	return (shk_cursor_read_escape(buf, x, y));
}
