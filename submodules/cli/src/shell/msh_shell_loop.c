/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_shell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 05:16:25 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/14 17:55:25 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <msh/minishell.h>
#include <msh/ast/tokenizer.h>
#include <msh/cli/shell.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

void	msh_shell_loop(t_minishell *msh)
{
	char	*line;
	char	*prompt;
	int		ret;

	if (!msh->interactive)
		rl_prep_term_function = 0;
	prompt = NULL;
	while (true)
	{
		if (msh->interactive)
			prompt = msh_prompt_bash(msh);
		line = readline(prompt);
		if (prompt)
			free(prompt);
		if (!line && msh->interactive)
			ft_dprintf(2, "exit\n");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		ret = msh_handle_line(msh, line);
		free(line);
		if (ret == -1)
			break ;
	}
}
