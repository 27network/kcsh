/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 21:34:39 by kiroussa          #+#    #+#             */
/*   Updated: 2024/03/25 15:59:36 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <ft/string.h>
#include <msh/builtin/defaults.h>
#include <stdio.h>

//TODO: @cglandus: Implement
static bool	msh_parse_numeric(const char *str, int *res)
{
	(void) str;
	*res = 0;
	return (true);
}

static void	msh_exit_help(t_minishell *msh, const char *argv0)
{
	printf("%s: %s [n]\n", argv0, argv0);
	printf("    Exit the shell.\n    \n");
	printf("    Exits the shell with a status of N.  "
		"If N is omitted, the exit status\n");
	printf("    is that of the last command executed.\n");
	msh_exit(msh, 0);
}

static int	msh_builtin_exit(int argc, char **argv, t_minishell *msh)
{
	int	ret;

	if (argc == 2 && !ft_strcmp(argv[1], "--help"))
		msh_exit_help(msh, argv[0]);
	printf("exit\n");
	if (argc == 1)
		return (-1);
	if (!msh_parse_numeric(argv[1], &ret))
	{
		ft_dprintf(2, "%s: exit: %s: numeric argument required\n",
			msh->name, argv[1]);
		msh->exit_code = 2;
		return (-1);
	}
	if (argc > 2)
	{
		ft_dprintf(2, "%s: exit: too many arguments\n", msh->name);
		return (1);
	}
	msh->exit_code = ret;
	return (-1);
}

__attribute__((constructor))
void	register_exit(void)
{
	msh_builtin_register((t_builtin){
		.name = "exit",
		.func = msh_builtin_exit,
		.needs = NEEDS_MSH,
	});
}
