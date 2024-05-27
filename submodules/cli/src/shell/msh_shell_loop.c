/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_shell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 05:16:25 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/27 07:50:02 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <ft/string/parse.h>
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
	char	*line;
	char	*prompt;

	prompt = NULL;
	while (msh->execution_context.running)
	{
		msh->execution_context.exit_code = 0;
		msh_update_env(msh, true);
		g_signal = -1;
		if (msh->interactive)
			prompt = msh_prompt_bash(msh);
		line = msh_input_forked(msh, prompt);
		if (prompt)
			free(prompt);
		msh_update_execution_context(msh);
		if ((!line || (line != (char *)1 && !*line)) && msh->interactive)
			ft_dprintf(2, "exit\n");
		if (!line || (line != (char *)1 && !*line))
			break ;
		msh_handle_line(msh, line);
		if (!msh->interactive && g_signal == SIGINT)
			break ;
	}
	if (line)
		free(line);
}
