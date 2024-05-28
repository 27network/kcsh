/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:44:25 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/27 16:11:06 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/io.h>
#include <ft/string.h>
#include <msh/cli/input.h>
#include <stdio.h>
#include <readline/readline.h>

#include <readline/history.h> //TODO: move this shit

t_input_result	msh_input(t_minishell *msh, const char *interactive_prompt)
{
	char				*line;
	t_input_result_type	type;
	size_t				size;

	if (msh->interactive)
	{
		line = readline(interactive_prompt);
		type = INPUT_OK;
		if (!line)
			type = INPUT_EOF;
		if (line && *line)
			add_history(line);
		return ((t_input_result){.type = type, .buffer = line});
	}
	line = get_next_line(msh->execution_context.file);
	type = INPUT_OK;
	size = ft_strlen(line);
	if (line[size - 1] == '\n')
		type = INPUT_EOF;
	if (line[size - 1] == '\n')
		line[size - 1] = 0;
	return ((t_input_result){.type = type, .buffer = line});
}
