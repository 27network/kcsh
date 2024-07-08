/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signal_handler_close_echo.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 05:13:10 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/08 23:48:48 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/signal.h>

void	msh_signal_echoctl(int signo);

void	msh_signal_handler_close_echo(int signo)
{
	msh_signal_echoctl(signo);
	msh_signal_handler_close(signo);
}
