/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 23:30:48 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/15 23:42:17 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/features.h>
#include <msh/builtin.h>
#include <stdio.h>

#define PWD_USAGE "pwd"
#define PWD_USAGE_OPT "pwd [-LP]"
#define PWD_HELP "Print the name of the current working directory.\n\
\n\
Exit Status:\n\
Returns 0 unless an invalid option is given or the current directory\n\
cannot be read."
#define PWD_HELP_OPT "Print the name of the current working directory.\n\
\n\
Options:\n\
  -L	print the value of $PWD if it names the current working\n\
		directory\n\
  -P	print the physical directory, without any symbolic links\n\
\n\
By default, `pwd' behaves as if `-L' were specified.\n\
\n\
Exit Status:\n\
Returns 0 unless an invalid option is given or the current directory\n\
cannot be read."

//TODO: Implement path traversal
static int	msh_builtin_pwd(int argc, char **argv, t_minishell *msh)
{
	(void) msh;
	if (argc == 1)
	{
		return (0);
	}
	if (!ft_strcmp(argv[1], "--help"))
	{
		msh_builtin_help_page(argv[0], 1);
		return (0);
	}
	return (0);
}

__attribute__((constructor))
void	register_pwd(void)
{
	char	*usage;
	char	*help;

	usage = PWD_USAGE;
	help = PWD_HELP;
	if (FEAT_BUILTIN_PWD_OPT)
	{
		usage = PWD_USAGE_OPT;
		help = PWD_HELP_OPT;
	}
	msh_builtin_register((t_builtin){
		.name = "pwd",
		.usage = usage,
		.help = help,
		.func = msh_builtin_pwd,
		.needs = NEEDS_MSH,
		.enabled = true,
	});
}
