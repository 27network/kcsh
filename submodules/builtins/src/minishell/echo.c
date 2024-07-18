/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouchet <ebouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 22:54:45 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/17 10:46:18 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/builtin.h>
#include <msh/env.h>
#include <msh/features.h>
#include <msh/util.h>
#include <stdlib.h>
#include <unistd.h>

#if FEAT_BUILTIN_ECHO_OPT
# define ECHO_USAGE "echo [-neE] [arg ...]"
# define ECHO_HELP "Write arguments to the standard output.\n\
\n\
Display the ARGs, separated by a single space character and followed by a\n\
newline, on the standard output.\n\
\n\
Options:\n\
  -n	do not append a newline\n\
  -e	enable interpretation of the following backslash escapes\n\
  -E	explicitly suppress interpretation of backslash escapes\n\
\n\
`echo' interprets the following backslash-escaped characters:\n\
  \\a	alert (bell)\n\
  \\b	backspace\n\
  \\c	suppress further output\n\
  \\f	form feed\n\
  \\n	new line\n\
  \\r	carriage return\n\
  \\t	horizontal tab\n\
  \\v	vertical tab\n\
  \\\\	backslash\n\
  \\0nnn	the character whose ASCII code is NNN (octal).  NNN can be\n\
		0 to 3 octal digits\n\
\n\
Exit Status:\n\
Returns success unless a write error occurs."
# define VALID_ECHO_OPTS "neE"
#else
# define ECHO_USAGE "echo [-n] [arg ...]"
# define ECHO_HELP "Write arguments to the standard output.\n\
\n\
Display the ARGs on the standard output followed by a newline.\n\
\n\
Options:\n\
  -n	do not append a newline\n\
\n\
Exit Status:\n\
Returns success unless a write error occurs."
# define VALID_ECHO_OPTS "n"
#endif // FEAT_BUILTIN_ECHO_OPT

static void	msh_echo_handle_opt(
	char opt,
	int *display_return,
	int *do_v9
) {
	if (opt == 'n')
		*display_return = 0;
	else if (opt == 'e')
		*do_v9 = 1;
	else if (opt == 'E')
		*do_v9 = 0;
}

static int	msh_echo_handle_opts(
	int argc,
	char **argv,
	int *display_return,
	int *do_v9
) {
	int		i;
	int		j;
	char	*arg;

	*display_return = 1;
	i = 1;
	while (i < argc)
	{
		arg = argv[i];
		if (*arg++ != '-')
			break ;
		j = 0;
		while (arg[j])
		{
			if (!ft_strchr(VALID_ECHO_OPTS, arg[j]))
				break ;
			j++;
		}
		if (*arg == 0 || arg[j])
			break ;
		while (*arg)
			msh_echo_handle_opt(*arg++, display_return, do_v9);
		i++;
	}
	return (i);
}

static void	msh_echo_write(
	__attribute__((unused)) t_minishell *msh,
	char *arg,
	int do_v9
) {
	char	*tmp;
	size_t	len;

	if (do_v9)
	{
		tmp = msh_ansicstr(arg, &len);
		if (!tmp)
			ft_putstr(arg);
		else
		{
			(void) !write(1, tmp, len);
			ft_strdel(&tmp);
		}
	}
	else
		ft_putstr(arg);
}

static int	msh_echo(
	int argc,
	char **argv,
	t_minishell *msh
) {
	int		display_return;
	int		do_v9;
	int		i;

	display_return = 1;
	do_v9 = FEAT_BUILTIN_ECHO_OPT && msh->flags.posix;
	if (msh->flags.posix)
		i = 1;
	else
		i = msh_echo_handle_opts(argc, argv, &display_return, &do_v9);
	while (i < argc)
	{
		msh_echo_write(msh, argv[i], do_v9);
		i++;
		if (i < argc)
			ft_putchar(' ');
	}
	if (display_return)
		ft_putchar('\n');
	return (0);
}

__attribute__((constructor))
void	register_echo(void)
{
	msh_builtin_register((t_builtin){
		.name = "echo",
		.usage = ECHO_USAGE,
		.help = ECHO_HELP,
		.func = msh_echo,
		.flags = BUILTIN_NEEDS_MSH,
	});
}
