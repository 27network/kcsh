/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 21:34:39 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/15 13:34:19 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <ft/string.h>
#include <msh/builtin/defaults.h>
#include <stdio.h>

#define EXIT_NAME "exit"
#define EXIT_USAGE "[n]"
#define EXIT_HELP "Exit the shell.\n\
\n\
Exits the shell with a status of N.  If N is omitted, the exit status\n\
is that of the last command executed."

//TODO: Implement
static bool	msh_parse_numeric(const char *str, int *res)
{
	(void) str;
	*res = 0;
	return (true);
}

static int	msh_builtin_exit(int argc, char **argv, t_minishell *msh)
{
	int	ret;

	if (argc == 2 && !ft_strcmp(argv[1], "--help"))
	{
		msh_builtin_print_help(EXIT_NAME, 1);
		return (0);
	}
	printf("exit\n");
	if (argc == 1)
		return (-1);
	if (!msh_parse_numeric(argv[1], &ret))
	{
		msh_error(msh, "%s: %s: numeric argument required\n",
			argv[0], argv[1]);
		msh->exit_code = 2;
		return (-1);
	}
	if (argc > 2)
	{
		msh_error(msh, "%s: too many arguments\n", argv[0]);
		return (1);
	}
	msh->exit_code = ret;
	return (-1);
}

__attribute__((constructor))
void	register_exit(void)
{
	msh_builtin_register((t_builtin){
		.name = EXIT_NAME,
		.usage = "[n]",
		.help = EXIT_HELP,
		.func = msh_builtin_exit,
		.needs = NEEDS_MSH,
		.enabled = true,
	});
}
