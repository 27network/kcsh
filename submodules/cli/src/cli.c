/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:46:03 by maldavid          #+#    #+#             */
/*   Updated: 2024/05/20 20:07:50 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/cli/opt.h>
#include <msh/cli/shell.h>
#include <msh/features.h>
#include <msh/minishell.h>
#include <msh/io.h>
#include <msh/signal.h>
#include <stdio.h>
#include <readline/readline.h>

int	main(int argc, const char *argv[], const char *envp[])
{
	t_minishell	minishell;

	msh_init(&minishell, argc, argv, envp);
	msh_signal_init(&minishell);
	rl_outstream = stderr;
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
	msh_shell_loop(&minishell);
	msh_destroy(&minishell);
	return (minishell.execution_context.exit_code);
}
