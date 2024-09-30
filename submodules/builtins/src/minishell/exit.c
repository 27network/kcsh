/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 21:34:39 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/30 08:44:06 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <ft/string.h>
#include <ft/string/parse.h>
#include <msh/builtin.h>
#include <msh/features.h>
#include <stdio.h>

#define EXIT_NAME "exit"
#define EXIT_USAGE "exit [n]"
#define EXIT_HELP "Exit the shell.\n\
\n\
Exits the shell with a status of N.  If N is omitted, the exit status\n\
is that of the last command executed."
#define LOGOUT_NAME "logout"
#define LOGOUT_USAGE "logout [n]"
#define LOGOUT_HELP "Exit the shell.\n\
\n\
Exits the shell with a status of N.  Returns an error if not executed\n\
in a login shell."

#define ERR_INVALID_ARG "%s: %s: numeric argument required\n"
#define ERR_TOO_MANY_ARGS "%s: too many arguments\n"

static bool	msh_parse_numeric(const char *str, int *res)
{
	long long				n;
	const t_str_parseerr	err = ft_strtoll(str, &n);

	if (err != PARSE_SUCCESS)
		return (false);
	*res = n;
	return (true);
}

static int	msh_exit_opts(t_minishell *msh, int argc, char **argv)
{
	if (!msh->flags.login && !ft_strcmp(argv[0], "logout"))
	{
		msh_error(msh, "logout: not login shell: use `exit'\n");
		return (1 + 1);
	}
	if (argc > 1)
	{
		if (!ft_strcmp(argv[1], "--"))
			return (0);
		if (!ft_strcmp(argv[1], "--help"))
		{
			msh_builtin_help_page(EXIT_NAME, 1);
			return (0 + 1);
		}
	}
	return (0);
}

void	msh_exit_dialog(t_minishell *msh, const char *program)
{
	if (!ft_strcmp(program, "logout"))
		return ;
	if (msh->flags.login)
		printf("logout\n");
	else
		printf("exit\n");
}

static int	msh_builtin_exit(int argc, char **argv, t_minishell *msh)
{
	int	ret;
	int	opt;

	opt = msh_exit_opts(msh, argc, argv);
	if (opt != 0)
		return (opt - 1);
	opt++;
	if (msh->interactive)
		msh_exit_dialog(msh, argv[0]);
	if (argc == 1 || opt == 2)
		msh->execution_context.running = false;
	if (argc == 1 || opt == 2)
		printf("exit_code: %d\n", msh->execution_context.exit_code);
	if (argc == 1 || opt == 2)
		return (msh->execution_context.exit_code);
	if (!msh_parse_numeric(argv[opt], &ret))
	{
		msh_error(msh, ERR_INVALID_ARG, argv[0], argv[opt]);
		msh->execution_context.running = false;
		return (2);
	}
	if (argc > opt + 1)
		msh_error(msh, ERR_TOO_MANY_ARGS, argv[0]);
	if (argc > opt + 1)
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
		.flags = BUILTIN_NEEDS_MSH | BUILTIN_SPECIAL,
	});
	msh_builtin_register((t_builtin){
		.name = LOGOUT_NAME,
		.usage = LOGOUT_USAGE,
		.help = LOGOUT_HELP,
		.func = msh_builtin_exit,
		.flags = BUILTIN_NEEDS_MSH | !FEAT_BUILTIN_LOGOUT << 2,
	});
}
