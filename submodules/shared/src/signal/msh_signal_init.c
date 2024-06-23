/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signal_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 05:10:08 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/23 04:16:00 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/signal.h>
#include <stdio.h>
#include <readline/readline.h>

int	g_signal = -1;

static void	msh_handle_continue(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
}

void	msh_signal_init(t_minishell *msh, bool close_stdin)
{
	t_signal_handler_fn	*sighandler;

	msh_signal_setdfl();
	rl_catch_signals = msh->interactive;
	if (msh->interactive && close_stdin)
		sighandler = &msh_signal_handler_close;
	else if (msh->interactive)
		sighandler = msh_signal_handler_interactive;
	else
		sighandler = msh_signal_handler_catch;
	signal(SIGINT, sighandler);
	if (msh->interactive)
		signal(SIGQUIT, SIG_IGN);
	else
		signal(SIGQUIT, sighandler);
	if (FEAT_JOB_CONTROL)
	{
		signal(SIGTSTP, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
	}
	else if (msh->interactive)
		signal(SIGCONT, msh_handle_continue);
}
