/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouchet <ebouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:04:11 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/01 15:15:03 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <ft/mem.h>
#include <msh/util.h>
#include <msh/builtin.h>
#include <msh/env.h>
#include <string.h>

#define CD_USAGE ""
#define CD_HELP ""

int	msh_cd_absolute(t_minishell *msh, const char *target);
int	msh_cd_relative(t_minishell *msh, const char *arg);
int	msh_cd_home(t_minishell *msh);
int	msh_cd_oldpwd(t_minishell *msh);

static inline int	msh_cd_enoent(t_minishell *msh)
{
	msh_error(msh, "cd: %s\n", strerror(ENOENT));
	return (1);
}

int	msh_builtin_cd(int argc, char **argv, t_minishell *msh)
{
	if (argc < 2)
		return (msh_cd_home(msh));
	else if (argc > 2)
		msh_error(msh, "cd: too many arguments\n");
	else
	{
		if (!msh->execution_context.cwd)
		{
			msh_warn(msh, "cd: cwd not set\n");
			msh_set_cwd(msh, NULL);
			if (!msh->execution_context.cwd)
				msh_error(msh, "cd: couldn't get cwd\n");
			if (!msh->execution_context.cwd)
				return (1);
		}
		if (argv[1][0] == '\0')
			return (msh_cd_enoent(msh));
		else if (argv[1][0] == '-' && argv[1][1] == '\0')
			return (msh_cd_oldpwd(msh));
		else if (argv[1][0] == '/')
			return (msh_cd_absolute(msh, argv[1]));
		else
			return (msh_cd_relative(msh, argv[1]));
	}
	return (1);
}

__attribute__((constructor))
void	register_cd(void)
{
	msh_builtin_register((t_builtin){
		.name = "cd",
		.usage = CD_USAGE,
		.help = CD_HELP,
		.func = msh_builtin_cd,
		.flags = BUILTIN_NEEDS_MSH,
	});
}
