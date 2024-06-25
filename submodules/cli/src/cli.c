/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:46:03 by maldavid          #+#    #+#             */
/*   Updated: 2024/06/25 05:32:02 by kiroussa         ###   ########.fr       */
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

#include <shakespeare.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef KCSH_TESTS

int	main(int argc, const char *argv[], const char *envp[])
{
	t_minishell	minishell;

	while (1)
	{
		char *line = shakespeare("> ");
		if (!line)
			exit(0);
		shk_history_push(line);
		printf("You entered: %s", line);
		fflush(stdout);
		free(line);
	}
	msh_builtin_registry_sort();
	(void) msh_history_raw();
	msh_init(&minishell, argc, argv, envp);
	msh_signal_init(&minishell, false);
	rl_outstream = stderr;
	if (!minishell.interactive)
		rl_prep_term_function = 0;
	if (argc != 1)
		msh_handle_opts(&minishell, argc, argv);
	msh_history_load(&minishell);
	msh_shell_loop(&minishell);
	msh_history_save(&minishell);
	msh_history_free();
	msh_destroy(&minishell);
	return (minishell.execution_context.exit_code);
}

#else

int	main(
	__attribute__((unused)) int argc,
	__attribute__((unused)) const char *argv[],
	__attribute__((unused)) const char *envp[]
) {
	return (0);
}

#endif // !KCSH_TESTS
