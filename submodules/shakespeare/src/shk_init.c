/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 06:08:33 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/23 07:07:10 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
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
	// disable mouse movement events
	shk->new_termios = shk->old_termios;
	shk->new_termios.c_lflag &= ~(ICANON | ECHO);
	shk->new_termios.c_cc[VMIN] = 1;
	shk->new_termios.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &shk->new_termios) == -1)
	{
		perror("tcsetattr");
		exit(EXIT_FAILURE);
	}
}

static void	shk_signal_handler(int signum, siginfo_t *info, void *context)
{
	t_shakespeare_data	*shk;

	(void)info;
	(void)context;
	if (signum == SIGINT)
	{
		ft_putstr_fd("^C\n", 2);
	}
	else if (signum == SIGWINCH)
	{
		shk = shk_shared();
		if (ioctl(STDIN_FILENO, TIOCGWINSZ, &shk->draw_ctx.terminal_size) < 0)
			perror("ioctl");
		// shk_redraw();
	}
}

static void	shk_setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = shk_signal_handler;
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
	shk_setup_termios(shk);
	shk_setup_signals();
}
