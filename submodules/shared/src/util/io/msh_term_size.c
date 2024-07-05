/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_term_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 03:08:05 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/05 16:02:29 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string/parse.h>
#include <msh/env.h>
#include <msh/features.h>
#include <msh/util.h>
#include <readline/readline.h>

#ifdef TIOCGWINSZ
# define SIZE_FETCHER ioctl_tiocgwinsz

static void	ioctl_tiocgwinsz(size_t *lines, size_t *col)
{
	int				tty;
	struct winsize	win;

	tty = STDIN_FILENO;
	if (!FEAT_NO_READLINE && rl_instream)
		tty = msh_fileno(rl_instream);
	if (tty >= 0 && ioctl(tty, TIOCGWINSZ, &win) == 0)
	{
		if (lines)
			*lines = win.ws_row;
		if (col)
			*col = win.ws_col;
	}
}

#else
# define SIZE_FETCHER fallback_overjump

static bool	msh_cursor_read_escape(char *buf, size_t *x, size_t *y)
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

bool	msh_get_cursor_pos(size_t *x, size_t *y)
{
	char	buf_write[33];
	char	*buf;

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
	return (msh_cursor_read_escape(buf, x, y));
}

static void	fallback_overjump(
	size_t *lines,
	size_t *col
) {
	size_t	old_x;
	size_t	old_y;

	if (!msh_get_cursor_pos(&old_x, &old_y))
		return ;
	write(1, "\033[999;999H", 9);
	if (msh_get_cursor_pos(col, lines))
		return ;
	*lines = 24;
	*col = 80;
}

#endif // TIOCGWINSZ

void	msh_term_size(t_minishell *msh, size_t *lines, size_t *cols)
{
	const char	*columns_env = msh_env_value(msh, "COLUMNS");
	const char	*lines_env = msh_env_value(msh, "LINES");

	ioctl_tiocgwinsz(lines, cols);
	if (lines && *lines == 0 && lines_env && *lines_env)
		*lines = ft_atoi(lines_env);
	if (cols && *cols == 0 && columns_env && *columns_env)
		*cols = ft_atoi(columns_env);
}
