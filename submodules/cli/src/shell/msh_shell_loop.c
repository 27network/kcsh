/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_shell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 05:16:25 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/28 23:48:46 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string/parse.h>
#include <ft/print.h>
#include <ft/string.h>
#include <msh/cli/history.h>
#include <msh/cli/input.h>
#include <msh/cli/shell.h>
#include <msh/env.h>
#include <msh/signal.h>
#include <msh/util.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>

static void	msh_update_env(t_minishell *msh, bool update_lineno)
{
	size_t	lines;
	size_t	cols;

	lines = 80;
	cols = 80;
	msh_term_size(msh, &lines, &cols);
	if (update_lineno)
		msh_env_push(msh, "LINENO", ft_itoa(msh->execution_context.line),
			ENV_ALLOC_VALUE);
	msh_env_push(msh, "COLUMNS", ft_itoa(cols), ENV_ALLOC_VALUE);
	msh_env_push(msh, "LINES", ft_itoa(lines), ENV_ALLOC_VALUE);
}

static void	msh_update_execution_context(t_minishell *msh)
{
	msh->execution_context.line++;
	if (g_signal != -1)
	{
		msh->execution_context.exit_code = 128 + g_signal;
		g_signal = -1;
	}
	msh_env_push(msh, "?", ft_itoa(msh->execution_context.exit_code),
		ENV_ALLOC_VALUE | ENV_INVISIBLE);
	msh_update_env(msh, false);
}

void	msh_shell_loop(t_minishell *msh)
{
	t_input_result	result;
	char			*prompt;

	prompt = NULL;
	msh_history_load(msh);
	while (msh->execution_context.running)
	{
		msh->execution_context.exit_code = 0;
		msh_update_env(msh, true);
		g_signal = -1;
		if (msh->interactive)
			prompt = msh_shell_prompt_parse(msh);
		result = msh_input_forked(msh, prompt);
		if (prompt)
			free(prompt);
		if (result.type == INPUT_IGNORED)
			break ;
		msh_update_execution_context(msh);
		msh_shell_handle_input(msh, result);
		if (!msh->interactive && (g_signal == SIGINT || g_signal == SIGQUIT))
			break ;
		if (result.type == INPUT_EOF)
			break ;
	}
	msh_history_save(msh);
}
