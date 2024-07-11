/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouchet <ebouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 00:49:32 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/11 16:27:27 by ebouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/builtin.h>
#include <msh/features.h>
#include <msh/env.h>
#include <msh/util.h>
#include <stdio.h>

#if FEAT_BUILTIN_SET_FULL
# define SET_USAGE "set [-abefhkmnptuvxBCHP] [-o option-name] [--] [arg ...]"
# define SET_HELP "\
Set or unset values of shell options and positional parameters.\n\
\n\
Change the value of shell attributes and positional parameters, or\n\
display the names and values of shell variables.\n\
\n\
Options:\n\
  -a  Mark variables which are modified or created for export.\n\
  -b  Notify of job termination immediately.\n\
  -e  Exit immediately if a command exits with a non-zero status.\n\
  -f  Disable file name generation (globbing).\n\
  -h  Remember the location of commands as they are looked up.\n\
  -k  All assignment arguments are placed in the environment for a command,\n\
	  not just those that precede the command name.\n\
  -m  Job control is enabled.\n\
  -n  Read commands but do not execute them.\n\
  -o option-name\n\
      Set the variable corresponding to option-name:\n\
          allexport    same as -a\n\
		  braceexpand  same as -B\n\
		  emacs        use an emacs-style line editing interface\n\
		  errexit      same as -e\n\
		  errtrace     same as -E\n\
		  functrace    same as -T\n\
		  hashall      same as -h\n\
		  histexpand   same as -H\n\
		  history      enable command history\n\
		  ignoreeof    the shell will not exit upon reading EOF\n\
		  interactive-comments\n\
					   allow comments to appear in interactive commands\n\
		  keyword      same as -k\n\
		  monitor      same as -m\n\
		  noclobber    same as -C\n\
		  noexec       same as -n\n\
		  noglob       same as -f\n\
		  nolog        currently accepted but ignored\n\
		  notify       same as -b\n\
		  nounset      same as -u\n\
		  onecmd       same as -t\n\
		  pipefail     the return value of a pipeline is the status of\n\
					   the last command to exit with a non-zero status,\n\
					   or zero if no command exited with a non-zero status\n\
		  posix        change the behavior of bash where the default\n\
					   operation differs from the POSIX standard to match\n\
					   the standard\n\
		  privileged   same as -p\n\
		  verbose      same as -v\n\
		  vi           use a vi-style line editing interface\n\
		  xtrace       same as -x\n\
  -p  Turned on whenever the real and effective user ids do not match.\n\
      Disables processing of the $ENV file and importing of shell\n\
	  functions.  Turning this option off causes the effective uid and\n\
	  gid to be set to the real uid and gid.\n\
  -t  Exit after reading and executing one command.\n\
  -u  Treat unset variables as an error when substituting.\n\
  -v  Print shell input lines as they are read.\n\
  -x  Print commands and their arguments as they are executed.\n\
  -B  the shell will perform brace expansion\n\
  -C  If set, disallow existing regular files to be overwritten by the\n\
	  redirection of output.\n\
  -E  If set, the ERR trap is inherited by shell functions.\n\
  -H  Enable ! style history substitution.  This flag is on\n\
	  by default when the shell is interactive.\n\
  -T  If set, the DEBUG and RETURN traps are inherited by shell functions.\n\
  --  Assign any remaining arguments to the positional parameters.\n\
      If there are no remaining arguments, the positional parameters\n\
	  are unset.\n\
  -   Assign any remaining arguments to the positional parameters.\n\
	  The -x and -v options are turned off.\n\
\n\
Using + rather than - causes these flags to be turned off.  The\n\
flags can also be used upon invocation of the shell.  The current\n\
set of flags may be found in $-.  The remaining n ARGs are positional\n\
parameters and are assigned, in order, to $1, $2, .. $n.  If no\n\
ARGs are given, all shell variables are printed.\n\
\n\
Exit Status:\n\
Returns success unless an invalid option is given.\n\
"
#else
# define SET_USAGE "set"
# define SET_HELP "\
Print all shell variables.\n\
\n\
Exit Status:\n\
Returns success.\n\
"
#endif

static void	msh_print_vars(t_minishell *msh)
{
	t_variable	*root;
	t_variable	*tmp;

	root = msh_env_sorted(msh);
	if (!root)
		msh_error(msh, "msh_print_vars: msh_env_sorted failed\n");
	if (!root)
		return ;
	while (root)
	{
		if (root->value && !(root->flags & ENV_INVISIBLE))
		{
			msh_env_print_assignment(msh, root, QUOTING_ANSI_C);
			printf("\n");
		}
		tmp = root;
		root = root->next;
		msh_env_free(msh, tmp);
	}
}

static int	msh_builtin_set(int argc, char **argv, t_minishell *msh)
{
	if (argc == 1 || !FEAT_BUILTIN_SET_FULL)
		msh_print_vars(msh);
	if (!FEAT_BUILTIN_SET_FULL)
		return (0);
	(void) argv;
	return (0);
}

__attribute__((constructor))
void	register_set(void)
{
	msh_builtin_register((t_builtin){
		.name = "set",
		.usage = SET_USAGE,
		.help = SET_HELP,
		.func = msh_builtin_set,
		.flags = !FEAT_BUILTIN_SET << 2 | BUILTIN_SPECIAL | BUILTIN_NEEDS_MSH,
	});
}
