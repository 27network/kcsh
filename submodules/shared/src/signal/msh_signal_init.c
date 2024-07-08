/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signal_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 05:10:08 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/07 23:46:05 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/features.h>
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

static void	msh_setup_echoctl(t_minishell *msh, bool close_stdin)
{
	(void) msh;
	(void) close_stdin;
	printf("we're missing a setup here\n");
}

static void	msh_setup_regular(t_minishell *msh, bool close_stdin)
{
	t_signal_handler_fn	*sighandler;

	if (msh->interactive && close_stdin)
		sighandler = &msh_signal_handler_close;
	else if (msh->interactive)
		sighandler = msh_signal_handler_interactive;
	else
		sighandler = msh_signal_handler_catch;
	signal(SIGINT, sighandler);
	if (msh->interactive)
		sighandler = SIG_IGN;
	signal(SIGQUIT, sighandler);
}

void	msh_signal_init(t_minishell *msh, bool close_stdin)
{
	msh_signal_setdfl();
	if (msh->term.c_lflag & ECHOCTL && msh->interactive)
		msh_setup_echoctl(msh, close_stdin);
	else
		msh_setup_regular(msh, close_stdin);
	if (FEAT_JOB_CONTROL)
	{
		signal(SIGTSTP, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
	}
	else if (msh->interactive)
		signal(SIGCONT, msh_handle_continue);
}
