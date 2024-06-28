/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_term_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 03:08:05 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/28 23:14:00 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string/parse.h>
#include <msh/env.h>
#include <msh/features.h>
#include <msh/util.h>
#include <readline/readline.h>

#ifdef TIOCGWINSZ

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

static void	ioctl_tiocgwinsz(
	__attribute__((unused)) size_t *lines,
	__attribute__((unused)) size_t *col
) {
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
