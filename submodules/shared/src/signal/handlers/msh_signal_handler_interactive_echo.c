/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signal_handler_interactive_echo.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:04:43 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/30 05:32:00 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/signal.h>
#include <stdio.h>

void	msh_signal_echoctl(int signo);

void	msh_signal_handler_interactive_echo(int signo)
{
	printf("interactive echo\n");
	msh_signal_echoctl(signo);
	msh_signal_handler_interactive(signo);
}
