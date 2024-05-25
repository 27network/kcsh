/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_shell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 05:16:25 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/25 01:58:00 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <msh/cli/input.h>
#include <msh/cli/shell.h>
#include <msh/signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>

static void	msh_update_execution_context(t_minishell *msh)
{
	msh->execution_context.line++;
	if (g_signal != -1)
	{
		msh->execution_context.exit_code = 128 + g_signal;
		g_signal = -1;
	}
}

void	msh_shell_loop(t_minishell *msh)
{
	char	*line;
	char	*prompt;

	if (!msh->interactive)
		rl_prep_term_function = 0;
	prompt = NULL;
	while (msh->execution_context.running)
	{
		g_signal = -1;
		if (msh->interactive)
			prompt = msh_prompt_bash(msh);
		line = msh_input(msh, prompt);
		if (prompt)
			free(prompt);
		msh_update_execution_context(msh);
		if (!line && msh->interactive)
			ft_dprintf(2, "exit\n");
		if (!line)
			break ;
		msh_handle_line(msh, line);
		free(line);
		if (!msh->interactive && g_signal == SIGINT)
			break ;
	}
}
