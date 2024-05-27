/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signal_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 05:10:08 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/27 07:36:27 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/signal.h>
#include <stdio.h>
#include <readline/readline.h>

void	msh_signal_init(t_minishell *msh, bool close_stdin)
{
	rl_catch_signals = msh->interactive;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	if (msh->interactive && close_stdin)
		signal(SIGINT, msh_signal_handler_close);
	else if (msh->interactive)
		signal(SIGINT, msh_signal_handler);
	else
		signal(SIGINT, msh_signal_handler_nonint);
}
