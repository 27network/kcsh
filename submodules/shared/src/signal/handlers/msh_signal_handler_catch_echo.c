/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signal_handler_catch_echo.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:06:04 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/08 23:48:32 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <msh/signal.h>
#include <unistd.h>

#if FEAT_NO_READLINE
# include <shakespeare.h>

void	msh_signal_echoctl(int signo)
{
	t_shakespeare_data	*shk;
	char				c;

	shk = shk_shared();
	if (signo == SIGINT)
		c = shk->old_termios.c_cc[VINTR];
	else if (signo == SIGQUIT)
		c = shk->old_termios.c_cc[VQUIT];
	else if (signo == SIGTSTP)
		c = shk->old_termios.c_cc[VSUSP];
	else
		return ;
	ft_putchar_fd('^', shk->draw.output_fd);
	ft_putchar_fd(c, shk->draw.output_fd);
}

#else

/**
 * Usually we'd try and get the chars from the termios struct, but I'd rather 
 * not use a static global just for this.
 */
void	msh_signal_echoctl(int signo)
{
	if (signo == SIGINT)
		ft_putstr_fd("^C", STDERR_FILENO);
	else if (signo == SIGQUIT)
		ft_putstr_fd("^\\", STDERR_FILENO);
	else if (signo == SIGTSTP)
		ft_putstr_fd("^Z", STDERR_FILENO);
}

#endif // FEAT_NO_READLINE

void	msh_signal_handler_catch_echo(int signo)
{
	msh_signal_echoctl(signo);
	msh_signal_handler_catch(signo);
}
