/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:46:03 by maldavid          #+#    #+#             */
/*   Updated: 2024/06/28 23:34:32 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/cli/history.h>
#include <msh/cli/opt.h>
#include <msh/cli/shell.h>
#include <msh/builtin.h>
#include <msh/features.h>
#include <msh/signal.h>
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
	msh_signal_init(&minishell, false);
	msh_setup_linelib(&minishell);
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
