/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_shell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 05:16:25 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/18 03:39:28 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <msh/signal.h>
#include <msh/cli/input.h>
#include <msh/cli/shell.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>

void	msh_shell_loop(t_minishell *msh)
{
	char	*line;
	char	*prompt;

	if (!msh->interactive)
		rl_prep_term_function = 0;
	prompt = NULL;
	while (msh->execution_context.running)
	{
		g_signal = 0;
		if (msh->interactive)
			prompt = msh_prompt_bash(msh);
		line = msh_input(msh, prompt);
		msh->execution_context.line++;
		if (prompt)
			free(prompt);
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
