/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:44:25 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/29 23:15:16 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/io.h>
#include <ft/string.h>
#include <msh/cli/input.h>
#include <stdio.h>
#include <readline/readline.h>

t_input_result	msh_input(t_minishell *msh, const char *interactive_prompt)
{
	char				*line;
	t_input_result_type	type;
	size_t				size;

	if (msh->interactive)
		return (msh_input_forked(msh, interactive_prompt));
	line = get_next_line(msh->execution_context.file);
	type = INPUT_OK;
	size = ft_strlen(line);
	if (line[size - 1] != '\n')
		type = INPUT_EOF;
	if (line[size - 1] == '\n')
		line[size - 1] = 0;
	return ((t_input_result){.type = type, .buffer = line});
}
