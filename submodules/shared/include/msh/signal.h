/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 05:09:18 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/12 16:10:23 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H
# undef SIGNAL_H
# ifndef __MSH_SIGNAL_H__
#  define __MSH_SIGNAL_H__

#  include <signal.h>

#  ifndef NSIG
#   ifdef _NSIG
#    define NSIG _NSIG
#   else
#    error "Invalid system configuration: NSIG or _NSIG aren't present"
#   endif // SIG
#  endif // !NSIG

#  include <msh/minishell.h>

extern int		g_signal;

typedef void	t_signal_handler_fn(int signo);

/**
 * @brief Initializes default signal handling for minishell.
 *
 * @param msh The minishell instance. 
 * @param close_stdin Whether to close stdin on SIGINT.
 */
void		msh_signal_init(t_minishell *msh, bool close_stdin);

/**
 * @brief Minishell's signal handler function.
 *
 * @param signum The signal number.
 */
void		msh_signal_handler_interactive(int signum);
void		msh_signal_handler_interactive_echo(int signum);

/**
 * @brief Minishell's signal handler function, non-interative edition:tm:
 *
 * @param signum The signal number.
 */
void		msh_signal_handler_catch(int signum);
void		msh_signal_handler_catch_echo(int signum);

/**
 * @brief Minishell's signal handler function, non-interative, stdin closing
 *																	edition:tm:
 *
 * @param signum The signal number.
 */
void		msh_signal_handler_close(int signum);
void		msh_signal_handler_close_echo(int signum);

/**
 * @brief Forces the signal handler for all signals to be reset to the default
 * signal handler.
 *
 * @note This function is used inside forks before calling `execve`.
 */
void		msh_signal_setdfl(void);

/**
 * @brief Returns the signal name for a given signal number.
 *
 * @param signum The signal number.
 *
 * @return The signal name.
 */
const char	*msh_strsignal(int signum);

# endif // __MSH_SIGNAL_H__
#endif // SIGNAL_H
