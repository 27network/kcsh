/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signal_handler_close.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 05:13:10 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/28 23:11:51 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <msh/signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <unistd.h>

void	msh_signal_handler_close(int signo)
{
	g_signal = signo;
	if (signo == SIGINT)
	{
		ft_putstr("\n");
		close(0);
	}
}
