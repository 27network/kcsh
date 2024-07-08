/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:55:22 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/07 05:23:40 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAGS_H
# define FLAGS_H
# undef FLAGS_H
# ifndef __MSH_FLAGS_H__
#  define __MSH_FLAGS_H__

#  include <stdbool.h>

typedef struct s_msh_flags
{
	// Debug flags
	bool	debug_generic;
	bool	debug_ast;
	bool	debug_executor;
	bool	debug_pipelines;
	bool	debug_sanitizer;
	bool	debug_tokenizer;
	// POSIX Flags
	bool	mark_modified_variables;	// -a allexport
	bool	exit_on_error;				// -e errexit
	bool	ignore_eof;					// ignoreeof
	bool	enable_job_control;			// -m monitor
	bool	no_clobber;					// -C noclobber
	bool	disallow_globbing;			// -f noglob
	bool	no_exec;					// -n noexec
	bool	no_log;						// nolog
	bool	async_notify;				// -b notify
	bool	unbound_is_error;			// -u nounset
	bool	verbose;					// -v verbose
	bool	vi;							// vi
	bool	xtrace;						// -x xtrace
	// POSIX Edge cases
	bool	hash_commands;				// -h hashall
	bool	args_to_assignment;			// -k keyword
	bool	just_once;					// -t onecmd
	// Bash
	bool	login;						// -l --login login
	bool	force_interactive;			// -i interactive
	bool	priviledged;				// -p privileged
	bool	restricted;
	bool	posix;
}	t_msh_flags;

# endif // __MSH_FLAGS_H__
#endif // FLAGS_H
