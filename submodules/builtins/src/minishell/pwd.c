/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 23:30:48 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/08 19:11:44 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/features.h>
#include <msh/builtin.h>
#include <stdio.h>

#if FEAT_BUILTIN_PWD_OPT
# define PWD_USAGE "pwd [-LP]"
# define PWD_HELP "Print the name of the current working directory.\n\
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
#else
# define PWD_USAGE "pwd"
# define PWD_HELP "Print the name of the current working directory.\n\
\n\
Exit Status:\n\
Returns 0 unless the current directory cannot be read."
#endif // FEAT_BUILTIN_PWD_OPT

#if FEAT_BUILTIN_PWD_OPT

//TODO: Implement options
static int	msh_builtin_pwd(int argc, char **argv, t_minishell *msh)
{
	if (argc > 1 && !ft_strcmp(argv[1], "--help"))
	{
		msh_builtin_help_page(argv[0], 1);
		return (0);
	}
	if (!msh->execution_context.cwd)
	{
		msh_error(msh, "msh_builtin_pwd: msh->execution_context.cwd is NULL\n");
		return (1);
	}
	printf("%s\n", msh->execution_context.cwd);
	return (0);
}

#else

static int	msh_builtin_pwd(int argc, char **argv, t_minishell *msh)
{
	if (argc > 1 && !ft_strcmp(argv[1], "--help"))
	{
		msh_builtin_help_page(argv[0], 1);
		return (0);
	}
	if (!msh->execution_context.cwd)
	{
		msh_error(msh, "msh_builtin_pwd: msh->execution_context.cwd is NULL\n");
		return (1);
	}
	printf("%s\n", msh->execution_context.cwd);
	return (0);
}

#endif // FEAT_BUILTIN_PWD_OPT

[[gnu::constructor]]
void	register_pwd(void)
{
	msh_builtin_register((t_builtin){
		.name = "pwd",
		.usage = PWD_USAGE,
		.help = PWD_HELP,
		.func = msh_builtin_pwd,
		.flags = BUILTIN_NEEDS_MSH,
	});
}
