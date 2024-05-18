/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:44:25 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/18 03:39:17 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/io.h>
#include <msh/cli/input.h>
#include <stdio.h>
#include <readline/readline.h>

char	*msh_input(t_minishell *msh, const char *interactive_prompt)
{
	if (msh->interactive)
		return (readline(interactive_prompt));
	return (get_next_line(msh->execution_context.file));
}
