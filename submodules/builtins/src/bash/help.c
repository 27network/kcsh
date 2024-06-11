/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:41:28 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/10 18:07:20 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <ft/mem.h>
#include <msh/builtin.h>
#include <msh/features.h>
#include <msh/util.h>
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

#define DISPLAY_BUFFER_SIZE 128

void	msh_print_version(int fd);

static void	display_col(size_t i, char *buffer, size_t width, size_t height)
{
	const size_t	count = msh_builtin_count(false);
	t_builtin		*builtin;

	ft_memset(buffer, ' ', DISPLAY_BUFFER_SIZE);
	builtin = msh_builtin_registry() + i;
	buffer[0] = ' ';
	if (!builtin->enabled)
		buffer[0] = '*';
	ft_strncpy(buffer + 1, builtin->usage, width - 2);
	ft_strncpy(buffer + width - 2, ">", 2);
	printf("%s", buffer);
	if ((i << 1) >= count || (i + height) >= count)
		return ;
	ft_memset(buffer, ' ', DISPLAY_BUFFER_SIZE);
	builtin = msh_builtin_registry() + (i + height);
	buffer[0] = ' ';
	if (!builtin->enabled)
		buffer[0] = '*';
	ft_strncpy(buffer + 1, builtin->usage, width - 2);
	ft_strncpy(buffer + width - 3, ">", 2);
	printf("%s", buffer);
}

static void	msh_help_command_wall(t_minishell *msh)
{
	size_t	width;
	size_t	height;
	size_t	cols;
	char	buffer[DISPLAY_BUFFER_SIZE];
	size_t	i;

	msh_term_size(msh, NULL, &cols);
	width = ft_min(DISPLAY_BUFFER_SIZE, cols / 2);
	if (width <= 3)
		width = 40;
	height = (msh_builtin_count(false) + 1) / 2;
	i = 0;
	while (i < height)
	{
		display_col(i, buffer, width, height);
		printf("\n");
		i++;
	}
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
