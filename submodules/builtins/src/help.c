/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:41:28 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/15 13:13:59 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/features.h>
#include <msh/builtin/defaults.h>

#define HELP_USAGE "[-dms] [pattern ...]"
#define HELP_HELP "Display information about builtin commands.\n\
\n\
Display brief summaries of builtin commands.  If PATTERN is\n\
specified, gives detailed help on all commands matching PATTERN,\n\
otherwise the list of help topics is printed.\n\
\n\
Options:\n\
  -d	output short description for each topic\n\
  -m	display usage in pseudo-manpage format\n\
  -s	output only a short usage synopsis for each topic matching PATTERN\n\

__attribute__((constructor))
void	register_help(void)
{
	msh_builtin_register((t_builtin){
		.name = "help",
		.usage = HELP_USAGE,
		.help = HELP_HELP,
		.func = msh_builtin_help,
		.enabled = FEAT_BUILTIN_HELP,
	});
}
