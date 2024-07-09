/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouchet <ebouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 23:07:57 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/09 18:35:58 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/builtin.h>
#include <msh/features.h>

#if FEAT_BUILTIN_EXPORT_OPT
# include <ft/opt.h>
# define EXPORT_USAGE "export [-fn] [name[=value] ...] or export -p"
# define VALID_OPTIONS "fnp"
# define EXPORT_HELP "\
Set export attribute for shell variables.\n\
\n\
Marks each NAME for automatic export to the environment of subsequently\n\
executed commands.  If VALUE is supplied, assign VALUE before exporting.\n\
\n\
Options:\n\
  -f        refer to function names only\n\
  -n        remove the export property from each NAME\n\
  -p        display all exported variables\n\
\n\
An argument of `--' disables further option processing.\n\
\n\
Exit Status:\n\
Returns success unless an invalid option is given or NAME is invalid.\n\
"
#else
# define EXPORT_USAGE "export [name[=value] ...]"
# define VALID_OPTIONS ""
# define EXPORT_HELP "\
Set export attribute for shell variables.\n\
\n\
Marks each NAME for automatic export to the environment of subsequently\n\
executed commands.  If VALUE is supplied, assign VALUE before exporting.\n\
\n\
Exit Status:\n\
Returns success unless NAME is invalid.\n\
"
#endif // FEAT_BUILTIN_EXPORT_OPT

int		msh_export_assign(t_minishell *msh, const char *arg);
void	msh_export_print(t_minishell *msh, const char *name);

#if FEAT_BUILTIN_EXPORT_OPT

#include <stdio.h>
static int	msh_export_assignments(t_minishell *msh, char **argv,
				bool function, bool negate)
{
	(void)msh;
	(void)argv;
	(void)function;
	(void)negate;
	// int		i;
	// int		ret;
	//
	// i = 0;
	// ret = 0;
	// while (i < args->argc)
	// {
	// 	if (msh_export_assign(msh, args->argv[i]))
	// 		ret = 1;
	// 	i++;
	// }
	printf("export assignments\n");
	// return (ret);
	return (0);
}

# define FLAG_PRINT 1
# define FLAG_FUNC 2
# define FLAG_NEG 4

static int	msh_export_arguments(t_minishell *msh, t_opt_args *args, int *flags)
{
	t_opt_globals	globals;
	int				c;

	globals = ft_opt_globals();
	globals.opterr = 0;
	while (1)
	{
		c = ft_opt_get(&globals, args);
		if (c == 'p')
			*flags |= FLAG_PRINT;
		if (c == 'p' || c == -1)
			break ;
		if (c == 'f')
			*flags |= FLAG_FUNC;
		if (c == 'n')
			*flags |= FLAG_NEG;
		if (c == '?')
			msh_error(msh, "export: -%c: invalid option\n", globals.optopt);
		// if (c == HELP_OPT)
			// msh_builtin_print_help(msh, "export");
		if (c == HELP_OPT || c == '?')
			return (c == '?');
	}
	return (0);
}

static int	msh_builtin_export(int argc, char **argv, t_minishell *msh)
{
	int			flags;
	t_opt_args	args;

	flags = 0;
	args = ft_opt_args(argc, argv, OPT_POSIX | OPT_BASH_LIKE, VALID_OPTIONS);
	if (argc == 1)
		flags |= FLAG_PRINT;
	else if (msh_export_arguments(msh, &args, &flags))
		return (1);
	if (flags & FLAG_PRINT)
		msh_export_print(msh, NULL);
	else
		return (msh_export_assignments(msh, argv, flags & FLAG_FUNC, flags & FLAG_NEG));
	return (0);
}

#else

static int	msh_builtin_export(int argc, char **argv, t_minishell *msh)
{
	int			i;
	int			ret;

	i = 1;
	ret = 0;
	if (argc == 1)
		msh_export_print(msh, argv[0]);
	else
	{
		while (argv[i])
		{
			if (msh_export_assign(msh, argv[i]))
				ret = 1;
			i++;
		}
	}
	return (ret);
}

#endif // FEAT_BUILTIN_EXPORT_OPT

__attribute__((constructor))
void	register_export(void)
{
	msh_builtin_register((t_builtin){
		.name = "export",
		.usage = EXPORT_USAGE,
		.help = EXPORT_HELP,
		.func = msh_builtin_export,
		.flags = BUILTIN_NEEDS_MSH | BUILTIN_SPECIAL,
	});
}
