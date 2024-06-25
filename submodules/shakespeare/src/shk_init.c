/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 06:08:33 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/25 07:08:48 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/print.h>
#include <ft/string.h>
#include <shakespeare.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	shk_setup_termios(t_shakespeare_data *shk)
{
	if (tcgetattr(STDIN_FILENO, &shk->old_termios) == -1)
	{
		perror("tcgetattr");
		exit(EXIT_FAILURE);
	}
	shk->new_termios = shk->old_termios;
	shk->new_termios.c_lflag &= ~(ICANON | ECHO | ISIG);
	// shk->new_termios.c_iflag &= ~INPCK;
	// shk->new_termios.c_iflag &= ~ISTRIP;
	shk->new_termios.c_cc[VMIN] = 1;
	shk->new_termios.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &shk->new_termios) == -1)
	{
		perror("tcsetattr");
		exit(EXIT_FAILURE);
	}
}

static void	shk_update_window(t_shakespeare_data *shk)
{
	char			buf[1024];
	char			*term;
	struct winsize	ws;

	term = getenv("TERM");
	if (term == NULL || !*term)
		term = "xterm-256color";
	shk->draw_ctx.tty_cols = -1;
	shk->draw_ctx.tty_rows = -1;
	if (tgetent(buf, term) != -1)
	{
		shk->draw_ctx.backspace = tgetstr("le", NULL);
		shk->draw_ctx.tty_cols = tgetnum("co");
		shk->draw_ctx.tty_rows = tgetnum("li");
	}
	if (shk->draw_ctx.tty_cols != -1 && shk->draw_ctx.tty_rows != -1)
		return ;
	ft_bzero(&ws, sizeof(ws));
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1)
		perror("ioctl");
	shk->draw_ctx.tty_cols = ws.ws_col + (!ws.ws_col * 80);
	shk->draw_ctx.tty_rows = ws.ws_row + (!ws.ws_row * 24);
}

static void	shk_signal_handler(int signum)
{
	t_shakespeare_data	*shk;

	if (signum == SIGINT)
	{
		ft_putstr_fd("^C\n", 2);
	}
	else if (signum == SIGWINCH)
	{
		shk = shk_shared();
		shk_update_window(shk);
		shk_redraw();
	}
}

static void	shk_setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = shk_signal_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGWINCH, &sa, NULL);
}

void	shk_init(t_shakespeare_data *shk)
{
	if (shk->initialized)
		return ;
	shk->initialized = true;
	shk->draw_ctx.output_fd = STDERR_FILENO;
	shk_setup_termios(shk);
	shk_setup_signals();
	shk_update_window(shk);
}
