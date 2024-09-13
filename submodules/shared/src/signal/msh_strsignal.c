/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_strsignal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:00:38 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/13 17:05:56 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string/parse.h>
#include <ft/string.h>
#include <ft/mem.h>
#include <signal.h>

#define UNKNOWN_SIGNAL "Unknown signal"

#if defined(SIGSTKFLT)
# define SIGTARGET SIGSTKFLT
# define SIGTARGET_MSG "Stack fault"
#elif defined(SIGEMT)
# define SIGTARGET SIGEMT
# define SIGTARGET_MSG "Emulator trap"
#else
# define SIGTARGET 16
# define SIGTARGET_MSG "Unknown signal"
#endif

#ifndef SIGRTMIN
# define SIGRTMIN 0
#endif

static inline const char	*msh_strsignal_rt(int signal)
{
	static char		buffer[32];
	char			*signbr;

	if (SIGRTMIN == 0)
		return (UNKNOWN_SIGNAL);
	if (signal - SIGRTMIN < 0)
		return (UNKNOWN_SIGNAL);
	ft_bzero(buffer, sizeof(buffer));
	ft_strlcpy(buffer, "Real-time signal ", sizeof(buffer));
	signbr = ft_lltoa(signal - SIGRTMIN);
	if (signbr == NULL)
		ft_strlcat(buffer, "unknown", sizeof(buffer));
	else
	{
		ft_strlcat(buffer, signbr, sizeof(buffer));
		free(signbr);
	}
	return (buffer);
}

const char	*msh_strsignal(int sigval)
{
	const char	*desc_map[] = {
	[SIGHUP] = "Hangup", [SIGINT] = "Interrupt", [SIGQUIT] = "Quit", [SIGILL]
		= "Illegal instruction", [SIGTRAP] = "Trace/breakpoint trap", [SIGABRT]
		= "Aborted", [SIGBUS] = "Bus error", [SIGFPE] = "Floating point "
		"exception", [SIGKILL] = "Killed", [SIGUSR1] = "User defined signal 1",
	[SIGSEGV] = "Segmentation fault", [SIGUSR2] = "User defined signal 2",
	[SIGPIPE] = "Broken pipe", [SIGALRM] = "Alarm clock", [SIGTERM]
		= "Terminated", [SIGTARGET] = SIGTARGET_MSG, [SIGCHLD] = "Child exited",
	[SIGCONT] = "Continued", [SIGSTOP] = "Stopped (signal)", [SIGTSTP]
		= "Stopped", [SIGTTIN] = "Stopped (tty input)", [SIGTTOU]
		= "Stopped (tty output)", [SIGURG] = "Urgent I/O condition", [SIGXCPU]
		= "CPU time limit exceeded", [SIGXFSZ] = "File size limit exceeded",
	[SIGVTALRM] = "Virtual timer expired", [SIGPROF]
		= "Profiling timer expired", [SIGWINCH] = "Window changed", [SIGIO]
		= "I/O possible", [SIGPWR] = "Power failure", [SIGSYS] = "Bad system "
		"call"
	};

	if (sigval < 0)
		return (UNKNOWN_SIGNAL);
	if (sigval > SIGSYS)
		return (msh_strsignal_rt(sigval));
	return (desc_map[sigval]);
}
