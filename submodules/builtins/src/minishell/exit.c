/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 21:34:39 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/19 03:59:47 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <ft/string.h>
#include <ft/string/parse.h>
#include <msh/builtin.h>
#include <stdio.h>

#define EXIT_NAME "exit"
#define EXIT_USAGE "exit [n]"
#define EXIT_HELP "Exit the shell.\n\
\n\
Exits the shell with a status of N.  If N is omitted, the exit status\n\
is that of the last command executed."

static bool	msh_parse_numeric(const char *str, int *res)
{
	long long				n;
	const t_str_parseerr	err = ft_strtoll(str, &n);

	if (err != PARSE_SUCCESS)
		return (false);
	*res = n;
	return (true);
}

static int	msh_builtin_exit(int argc, char **argv, t_minishell *msh)
{
	int	ret;

	if (argc == 2 && !ft_strcmp(argv[1], "--help"))
		msh_builtin_help_page(EXIT_NAME, 1);
	if (argc == 2 && !ft_strcmp(argv[1], "--help"))
		return (0);
	if (msh->interactive)
		printf("exit\n");
	if (argc == 1)
		msh->execution_context.running = false;
	if (argc == 1)
		return (msh->execution_context.exit_code);
	if (!msh_parse_numeric(argv[1], &ret))
	{
		msh_error(msh, "%s: %s: numeric argument required\n",
			argv[0], argv[1]);
		msh->execution_context.running = false;
		return (2);
	}
	if (argc > 2)
		msh_error(msh, "%s: too many arguments\n", argv[0]);
	if (argc > 2)
		return (1);
	msh->execution_context.running = false;
	return (ret);
}

__attribute__((constructor))
void	register_exit(void)
{
	msh_builtin_register((t_builtin){
		.name = EXIT_NAME,
		.usage = EXIT_USAGE,
		.help = EXIT_HELP,
		.func = msh_builtin_exit,
		.needs = NEEDS_MSH,
		.enabled = true,
	});
}
