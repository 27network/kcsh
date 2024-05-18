/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:41:28 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/17 03:24:13 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <msh/builtin.h>
#include <msh/features.h>
#include <msh/io.h>
#include <stdio.h>

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

void	msh_print_version(int fd);

static void	msh_help_command_wall(t_minishell *msh)
{
	size_t	width;
	size_t	height;

	width = ft_min(128, msh_columns(msh) / 2);
	if (width <= 3)
		width = 40;
	height = (msh_builtin_count() + 1) / 2;
	(void) width;
	(void) height;
}

static int	msh_help(
	int argc,
	ATTR((unused)) char **argv,
	t_minishell *msh
) {
	if (argc == 1)
	{
		msh_print_version(1);
		printf("These shell commands are defined internally.  Type `help'"
			" to see this list.\nType `help name' to find out more about the "
			"function `name'.\nUse `man -k' or `info' to find out more about "
			"commands not in this list.\n\nA star (*) next to a name means "
			"that the command is disabled.\n\n");
		msh_help_command_wall(msh);
		return (0);
	}
	else
	{
	}
	return (0);
}

__attribute__((constructor))
void	register_help(void)
{
	msh_builtin_register((t_builtin){
		.name = "help",
		.usage = HELP_USAGE,
		.help = HELP_HELP,
		.func = msh_help,
		.needs = NEEDS_MSH,
		.enabled = FEAT_BUILTIN_HELP,
	});
}
