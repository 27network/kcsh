/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_input_wrap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:09:04 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/01 11:52:33 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <ft/string.h>
#include <msh/cli/input.h>
#include <msh/log.h>
#include <msh/minishell.h>
#include <msh/util.h>
#include <string.h>
#include <stdlib.h>

char	*msh_input_wrap(t_minishell *msh, const char *prompt, const char *delim,
			bool *borked)
{
	t_input_result	input;

	input = msh_input(msh, prompt);
	if (input.type == INPUT_ERROR)
	{
		msh_error(msh, "failed to read input: %s\n", strerror(errno));
		return (NULL);
	}
	if (input.type == INPUT_EOF)
		msh_error(msh, "warning: here-document at line %d delimited by end-"
			"of-file (wanted `%s')\n", (int)msh->execution_context.line, delim);
	if (input.type == INPUT_INTERRUPTED)
		*borked = true;
	if (input.type == INPUT_EOF || input.type == INPUT_INTERRUPTED)
		return (NULL);
	return (input.buffer);
}
