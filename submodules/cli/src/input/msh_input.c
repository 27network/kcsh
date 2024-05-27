/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:44:25 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/27 07:21:00 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/io.h>
#include <ft/string.h>
#include <msh/cli/input.h>
#include <stdio.h>
#include <readline/readline.h>

#include <readline/history.h> //TODO: move this shit

char	*msh_input(t_minishell *msh, const char *interactive_prompt)
{
	char	*line;

	if (msh->interactive)
	{
		line = readline(interactive_prompt);
		if (!line)
			return (ft_strdup(""));
		if (*line)
			add_history(line);
		return (ft_strjoins(2, "", 0b10, line, "\n"));
	}
	return (get_next_line(msh->execution_context.file));
}
