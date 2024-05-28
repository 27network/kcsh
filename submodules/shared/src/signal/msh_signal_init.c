/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signal_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 05:10:08 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/28 12:12:04 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/signal.h>
#include <stdio.h>
#include <readline/readline.h>

int	g_signal = -1;

void	msh_signal_init(t_minishell *msh, bool close_stdin)
{
	t_signal_handler_fn	*sighandler;

	msh_signal_setdfl();
	rl_catch_signals = msh->interactive;
	signal(SIGTSTP, SIG_IGN);
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
}
