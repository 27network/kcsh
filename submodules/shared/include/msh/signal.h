/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 05:09:18 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/14 13:01:44 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H
# undef SIGNAL_H
# ifndef __MSH_SIGNAL_H__
#  define __MSH_SIGNAL_H__

#  ifndef NSIG
#   ifndef __USE_MISC
#    define __USE_POSIX19930
#    define __USE_MISC
#   endif // !__USE_MISC
#  endif // !NSIG

#  include <signal.h>
#  include <msh/minishell.h>

extern int	g_signal;

/**
 * @brief Initializes default signal handling for minishell.
 *
 * @param msh The minishell instance. 
 */
void		msh_signal_init(t_minishell *msh);

/**
 * @brief Minishell's mode-independant signal handler function.
 *
 * @param signum The signal number.
 */
void		msh_signal_handler(int signum);

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
