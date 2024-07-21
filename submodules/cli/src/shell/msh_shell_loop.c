/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_shell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 05:16:25 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/21 17:17:57 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string/parse.h>
#include <ft/print.h>
#include <ft/string.h>
#include <msh/cli/history.h>
#include <msh/cli/input.h>
#include <msh/cli/shell.h>
#include <msh/env.h>
#include <msh/log.h>
#include <msh/signal.h>
#include <msh/util.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>

static void	msh_update_env(t_minishell *msh, bool update_lineno)
{
	size_t	lines;
	size_t	cols;

	g_signal = -1;
	if (update_lineno)
		msh_env_push(msh, "LINENO", ft_itoa(msh->execution_context.line),
			ENV_ALLOC_VALUE | ENV_INVISIBLE | ENV_INTEGER);
	if (!msh->interactive)
		return ;
	lines = 80;
	cols = 80;
	msh_term_size(msh, &lines, &cols);
	msh_env_push(msh, "COLUMNS", ft_itoa(cols), ENV_ALLOC_VALUE | ENV_INTEGER);
	msh_env_push(msh, "LINES", ft_itoa(lines), ENV_ALLOC_VALUE | ENV_INTEGER);
}

static void	msh_update_execution_context(t_minishell *msh,
				t_input_result result)
{
	msh->execution_context.line++;
	if (result.type == INPUT_EOF)
		msh->execution_context.running = false;
	if (result.type == INPUT_INTERRUPTED)
		msh->execution_context.exit_code = 128 + SIGINT;
	if (result.type == INPUT_ERROR)
	{
		msh_error(msh, "input: an error occured while reading input\n");
		msh->execution_context.exit_code = 2;
	}
	msh_env_push(msh, "?", ft_itoa(msh->execution_context.exit_code),
		ENV_ALLOC_VALUE | ENV_INVISIBLE | ENV_NO_UNSET | ENV_INTEGER);
	msh_update_env(msh, false);
}

void	msh_exit_dialog(t_minishell *msh, const char *program);

void	msh_shell_loop(t_minishell *msh)
{
	t_input_result	result;
	char			*prompt;

	prompt = NULL;
	while (msh->execution_context.running && !msh->forked)
	{
		msh_update_env(msh, true);
		if (msh->interactive)
			prompt = msh_shell_prompt_parse(msh);
		result = msh_input(msh, prompt);
		if (prompt)
			free(prompt);
		if (msh->forked)
			break ;
		msh_update_execution_context(msh, result);
		if (result.type == INPUT_INTERRUPTED)
			continue ;
		msh_shell_handle_input(msh, result);
		if (result.type == INPUT_EOF && msh->interactive)
			msh_exit_dialog(msh, "exit");
	}
}
