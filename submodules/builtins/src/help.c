/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:41:28 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/15 23:18:06 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/features.h>
#include <msh/builtin.h>

#define HELP_USAGE "help [-dms] [pattern ...]"
#define HELP_HELP "Display information about builtin commands.\n\
\n\
Display brief summaries of builtin commands.  If PATTERN is\n\
specified, gives detailed help on all commands matching PATTERN,\n\
otherwise the list of help topics is printed.\n\
\n\
Options:\n\
  -d	output short description for each topic\n\
  -m	display usage in pseudo-manpage format\n\
  -s	output only a short usage synopsis for each topic matching PATTERN"

#define DISPLAY_LONG_DESC 0
#define DISPLAY_SHORT_DESC 1
#define DISPLAY_MANPAGE 2
#define DISPLAY_SHORT_USAGE 4

static int	msh_help(
	ATTR((unused)) int argc,
	ATTR((unused)) char **argv
) {
	return (0);
}

ATTR((constructor))
void	register_help(void)
{
	msh_builtin_register((t_builtin){
		.name = "help",
		.usage = HELP_USAGE,
		.help = HELP_HELP,
		.func = msh_help,
		.enabled = FEAT_BUILTIN_HELP,
	});
}
