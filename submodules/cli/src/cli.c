/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:46:03 by maldavid          #+#    #+#             */
/*   Updated: 2024/05/31 17:10:53 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/cli/history.h>
#include <msh/cli/opt.h>
#include <msh/cli/shell.h>
#include <msh/builtin.h>
#include <msh/features.h>
#include <msh/signal.h>
#include <msh/util.h>
#include <readline/readline.h>

int	main(int argc, const char *argv[], const char *envp[])
{
	t_minishell	minishell;

	msh_builtin_registry_sort();
	(void) msh_history_raw();
	msh_init(&minishell, argc, argv, envp);
	msh_signal_init(&minishell, false);
	rl_outstream = stderr;
	if (!minishell.interactive)
		rl_prep_term_function = 0;
	if (argc != 1)
	{
		if (FEAT_COMMAND_LINE_INTERFACE)
			msh_handle_opts(&minishell, argc, argv);
		else
		{
			msh_error(&minishell, "command line options are disabled\n");
			msh_exit(&minishell, 1);
		}
	}
	msh_history_load(&minishell);
	msh_shell_loop(&minishell);
	msh_history_save(&minishell);
	msh_history_free();
	msh_destroy(&minishell);
	return (minishell.execution_context.exit_code);
}
