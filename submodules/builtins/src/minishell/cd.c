/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouchet <ebouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:04:11 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/15 18:21:31 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <msh/util.h>
#include <msh/builtin.h>
#include <msh/env.h>
#include <ft/mem.h>
#include <string.h>
#include <unistd.h>

#define CD_USAGE ""
#define CD_HELP ""


// cd => chdir($HOME)
// cd ~ => chdir(msh_expand_tilde(arg))
// cd - => chdir($OLDPWD)
// cd ../difew => chdir(cwd / arg)
// cd /home/ptdr => chdir(arg)

/*
int	msh_cd_tilde(int argc, char **argv, t_minishell *msh)
{

}
*/

int	msh_cd_oldpwd(t_minishell *msh)
{
	const char	*target;
	int			ret;

	target = msh_env_value(msh, "OLDPWD");
	if (!target)
		msh_error(msh, "cd: OLDPWD not set\n");
	if (!target)
		return (1);
	ret = chdir(target);
	if (ret != 0)
		msh_error(msh, "cd: %s: %s\n", target, strerror(errno));
	msh_set_cwd(msh, target);
	return (ret);
}

int	msh_cd_relative(t_minishell *msh, const char *arg)
{
	(void) msh;
	(void) arg;
	return (0);
}

int	msh_cd_absolute(t_minishell *msh, const char *target)
{
	int	ret;

	if (!target)
		return (1);
	ret = chdir(target);
	if (ret != 0)
		msh_error(msh, "cd: %s: %s\n", target, strerror(errno));
	if (ret != 0)
		return (1);
	target = msh_canonicalize(target);
	if (!target)
		msh_warn(msh, "cd: couldn't canonicalize path, fallback to cwd\n");
	if (!target)
		target = getcwd(NULL, 0);
	if (!target)
		msh_error(msh, "cd: getcwd: allocation error\n");
	else
		msh_set_cwd(msh, target);
	return (ret != 0 || target == NULL);
}

int	msh_cd_home(t_minishell *msh)
{
	const char	*target;
	
	target = msh_env_value(msh, "HOME");
	if (!target)
	{
		msh_error(msh, "cd: HOME not set\n");
		return (1);
	}
	return (msh_cd_absolute(msh, target));
}

int	msh_builtin_cd(int argc, char **argv, t_minishell *msh)
{
	if (argc < 2)
		return (msh_cd_home(msh));
	else if (argc > 2)
		msh_error(msh, "cd: too many arguments\n");
	else
	{
		if (argv[1][0] == '-' && argv[1][1] == '\0')
			msh_cd_oldpwd(msh);
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
		.flags = BUILTIN_NEEDS_MSH | BUILTIN_SPECIAL,
	});
}
