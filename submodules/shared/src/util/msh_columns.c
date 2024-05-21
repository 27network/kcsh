/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_columns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 03:08:05 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/21 23:38:31 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string/parse.h>
#include <msh/env.h>
#include <msh/util.h>
#include <readline/readline.h>

#ifdef TIOCGWINSZ

static void	ioctl_tiocgwinsz(int *col)
{
	int				tty;
	struct winsize	win;

	tty = STDIN_FILENO;
	if (rl_instream)
		tty = msh_fileno(rl_instream);
	if (tty >= 0 && ioctl(tty, TIOCGWINSZ, &win) == 0 && win.ws_col > 0)
		*col = win.ws_col;
}

#else

static void	ioctl_tiocgwinsz(__attribute__((unused)) int *col)
{
}

#endif // TIOCGWINSZ

size_t	msh_columns(t_minishell *msh)
{
	int			value;
	const char	*columns_env = msh_env_value(msh, "COLUMNS");

	value = 80;
	if (columns_env && *columns_env)
	{
		value = ft_atoi(columns_env);
		if (value > 0)
			return ((size_t) value);
	}
	ioctl_tiocgwinsz(&value);
	if (value > 0)
		return (value);
	return (80);
}
