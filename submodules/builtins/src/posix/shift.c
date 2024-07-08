/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:49:59 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/08 20:06:44 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string/parse.h>
#include <ft/string.h>
#include <msh/builtin.h>
#include <msh/features.h>

#define SHIFT_USAGE "shift [n]"
#define SHIFT_HELP "Shift positional parameters.\n\
\n\
Rename the positional parameters $N+1,$N+2 ... to $1,$2 ... If N is\n\
not given, it is assumed to be 1.\n\
\n\
Exit Status:\n\
Returns success unless N is negative or greater than $#."

static int	msh_shift(t_minishell *msh, int by)
{
	t_program_args	*args;
	const char		*argv0;

	args = &msh->execution_context.shell_args;
	if (!args)
	{
		msh_error(msh, "shift: msh->execution_context.shell_args is NULL\n");
		return (1);
	}
	if (by > args->argc - 1)
		return (1);
	if (by == 0)
		return (0);
	argv0 = args->argv[0];
	args->argc -= by;
	args->argv += by;
	args->argv[0] = argv0;
	return (0);
}

static int	msh_builtin_shift(int argc, char **argv, t_minishell *msh)
{
	const int		nargs = !ft_strcmp(argv[1], "--") + 1;
	long long		n;
	t_str_parseerr	err;

	n = 1;
	if (argc > nargs)
	{
		err = ft_strtoll(argv[nargs], &n);
		if (err != PARSE_SUCCESS)
		{
			msh_error(msh, "shift: %s: numeric argument required\n",
				argv[nargs]);
			return (1);
		}
		if (n < 0)
		{
			msh_error(msh, "shift: %s: shift count out of range\n",
				argv[nargs]);
			return (1);
		}
	}
	return (msh_shift(msh, n));
}

__attribute__((constructor))
void	register_shift(void)
{
	msh_builtin_register((t_builtin){
		.name = "shift",
		.usage = SHIFT_USAGE,
		.help = SHIFT_HELP,
		.func = msh_builtin_shift,
		.flags = !FEAT_BUILTIN_SHIFT << 2,
	});
}
