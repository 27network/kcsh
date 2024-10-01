/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:46:03 by maldavid          #+#    #+#             */
/*   Updated: 2024/10/01 16:44:21 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/cli/history.h>
#include <msh/cli/opt.h>
#include <msh/cli/shell.h>
#include <msh/builtin.h>
#include <msh/features.h>
#include <msh/util.h>

#if FEAT_NO_READLINE
# include <shakespeare.h>
#else
# include <readline/readline.h>
#endif

#ifndef KCSH_TESTS
# if !FEAT_NO_READLINE

static void	msh_setup_linelib(t_minishell *msh)
{
	(void) msh_history_raw();
	rl_outstream = stderr;
	if (!msh->interactive)
		rl_prep_term_function = 0;
}

# else

static void	msh_setup_linelib(
	__attribute__((unused)) t_minishell *msh
) {
}

# endif // !FEAT_NO_READLINE

int	main(int argc, const char *argv[], const char *envp[])
{
	t_minishell	minishell;

	msh_builtin_registry_sort();
	msh_init(&minishell, argc, argv, envp);
	msh_setup_linelib(&minishell);
	if (argc != 1 && FEAT_CLI_OPTS)
		msh_handle_opts(&minishell, argc, argv);
	else if (argc != 1)
	{
		ft_dprintf(STDERR_FILENO, "usage: %s\n", argv[0]);
		minishell.execution_context.exit_code = 1;
	}
	if (argc == 1 || FEAT_CLI_OPTS)
	{
		msh_history_load(&minishell);
		msh_shell_loop(&minishell);
		msh_history_save(&minishell);
		msh_history_free();
	}
	if (minishell.flags.debug_executor)
		msh_log(&minishell, MSG_DEBUG_EXECUTOR, "pid %d exited with "
			"code %d\n", msh_getpid(), minishell.execution_context.exit_code);
	msh_destroy(&minishell);
	return (minishell.execution_context.exit_code);
}

#else

int	main(void)
{
	ft_dprintf(STDERR_FILENO, "\n\t👍 all tests ran, did it explode? 💥\n\n");
	return (0);
}

#endif // !KCSH_TESTS
