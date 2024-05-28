/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:46:03 by maldavid          #+#    #+#             */
/*   Updated: 2024/05/29 00:03:11 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <msh/cli/history.h>
#include <msh/cli/opt.h>
#include <msh/cli/shell.h>
#include <msh/builtin.h>
#include <msh/features.h>
#include <msh/minishell.h>
#include <msh/util.h>
#include <msh/signal.h>
#include <stdio.h>
#include <readline/readline.h>

static void	msh_swap(t_builtin *a, t_builtin *b, size_t size)
{
	t_builtin	tmp;

	ft_memcpy(&tmp, a, size);
	ft_memcpy(a, b, size);
	ft_memcpy(b, &tmp, size);
}

static void	msh_sort_builtins_registry(void)
{
	t_builtin	*registry;
	size_t		size;
	size_t		i;
	size_t		min_idx;
	size_t		j;

	registry = msh_builtin_registry();
	size = msh_builtin_count(true);
	i = 0;
	while (i < size - 1)
	{
		min_idx = i;
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(registry[j].name, registry[min_idx].name) < 0)
				min_idx = j;
			j++;
		}
		if (min_idx != i)
			msh_swap(&registry[i], &registry[min_idx], sizeof(t_builtin));
		i++;
	}
}

int	main(int argc, const char *argv[], const char *envp[])
{
	t_minishell	minishell;

	(void) msh_history_raw();
	msh_sort_builtins_registry();
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
	msh_shell_loop(&minishell);
	msh_destroy(&minishell);
	return (minishell.execution_context.exit_code);
}
