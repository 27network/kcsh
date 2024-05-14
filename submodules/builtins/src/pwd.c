/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 23:30:48 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/14 13:39:31 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/builtin/defaults.h>
#include <stdio.h>

#define FEAT_BUILTIN_PWD_OPT 1

static void	msh_pwd_help(const char *argv0)
{
	printf("%s: %s", argv0, argv0);
	if (FEAT_BUILTIN_PWD_OPT)
		printf(" [-LP]");
	printf("\n    Print the name of the current working directory.\n    ");
	if (FEAT_BUILTIN_PWD_OPT)
	{
		printf("\n    Options:\n");
		printf("      -L	print the value of $PWD if it names the "
			"current working\n    		directory\n");
		printf("      -P	print the physical directory, without any "
			"symbolic links\n    \n    ");
		printf("By default, `%s' behaves as if `-L' were specified.\n    ",
			argv0);
	}
	printf("\n    Exit Status:\n    Returns 0 unless an invalid "
		"option is given or the current directory\n    cannot be read.\n");
}

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
		msh_pwd_help(argv[0]);
		return (0);
	}
	return (0);
}

__attribute__((constructor))
void	register_pwd(void)
{
	msh_builtin_register((t_builtin){
		.name = "pwd",
		.func = msh_builtin_pwd,
		.needs = NEEDS_MSH,
	});
}
