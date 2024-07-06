/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_term_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 03:08:05 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/07 00:58:42 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/print.h>
#include <ft/string.h>
#include <ft/string/parse.h>
#include <msh/env.h>
#include <msh/features.h>
#include <msh/util.h>
#include <readline/readline.h>
#include <sys/ioctl.h>
#include <unistd.h>

#if FEAT_NO_READLINE
# include <shakespeare.h>
# define FALLBACK shk_cursor_pos_abs_wrapper

static void	shk_cursor_pos_abs_wrapper(size_t *lines, size_t *cols)
{
	shk_cursor_pos_abs(NULL, lines, cols);
}

#else
# define FALLBACK no_op

static void	no_op(size_t *lines, size_t *cols)
{
	(void)lines;
	(void)cols;
}
#endif // FEAT_NO_READLINE

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
	else
		FALLBACK(lines, col);
}

#else
# if FEAT_NO_READLINE
#  define SIZE_FETCHER shk_cursor_pos_abs_wrapper
# else
#  define SIZE_FETCHER no_op
# endif // FEAT_NO_READLINE
#endif // TIOCGWINSZ

void	msh_term_size(t_minishell *msh, size_t *lines, size_t *cols)
{
	const char	*columns_env = msh_env_value(msh, "COLUMNS");
	const char	*lines_env = msh_env_value(msh, "LINES");

	SIZE_FETCHER(lines, cols);
	if (lines && *lines == 0 && lines_env && *lines_env)
		*lines = ft_atoi(lines_env);
	if (cols && *cols == 0 && columns_env && *columns_env)
		*cols = ft_atoi(columns_env);
}
