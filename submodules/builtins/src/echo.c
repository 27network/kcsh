/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 22:54:45 by kiroussa          #+#    #+#             */
/*   Updated: 2024/03/28 21:09:43 by cglandus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/builtin/defaults.h>

static int	is_opt(char *arg, const char *set, t_echo_opt *opt)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (ft_strchr(set, arg[i]) == 0)
			return (0);
		if ((arg[i] == 'e' || arg[i] == 'E') && !ECHO_OPT)
			return (0);
		if (arg[i] == 'n' && ((ft_strchr(arg, 'e') == 0
					&& ft_strchr(arg, 'E') == 0) || ECHO_OPT))
			opt->no_nl = true;
		else if (arg[i] == 'e')
			opt->bslh_enable = true;
		else if (arg[i] == 'E')
			opt->bslh_enable = false;
		i++;
	}
	return (1);
}

static int	opt_skip(char **argv, t_echo_opt *opt)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (argv[i][0] != '-' || ft_strlen(argv[i]) < 2)
			break ;
		if (!is_opt(argv[i], "neE", opt)
			|| (!ECHO_OPT && !is_opt(argv[i], "n", opt)))
			break ;
		i++;
	}
	return (i);
}

static void	ft_putbslh(char *format, t_echo_opt *opt)
{
	int	i;

	i = 0;
	while (format[i])
	{
		if (format[i] == '\\' && opt->bslh_enable && ECHO_OPT)
		{
			if (format[i + 1] == '\\')
				ft_putchar('\\');
			if (format[i + 1] == 'n')
				ft_putchar('\n');
			if (format[i + 1] == 't')
				ft_putchar('\t');
			else
				ft_putchar('Q');
			i++;
		}
		else
			ft_putchar(format[i]);
		i++;
	}
}

static int	msh_builtin_echo(int argc, char **argv)
{
	int			i;
	t_echo_opt	opt;

	(void) argc;
	(void) argv;
	opt.no_nl = false;
	opt.bslh_enable = false;
	if (argc < 2)
		ft_putchar('\n');
	else
	{
		i = opt_skip(argv, &opt);
		while (argv[i])
		{
			ft_putbslh(argv[i], &opt);
			i++;
			if (argv[i])
				ft_putchar(' ');
		}
		if (!opt.no_nl)
			ft_putchar('\n');
	}
	return (0);
}

__attribute__((constructor))
void	register_echo(void)
{
	msh_builtin_register((t_builtin){
		.name = "echo",
		.func = msh_builtin_echo,
	});
}
