/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouchet <ebouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 23:07:57 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/09 14:49:30 by ebouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/builtin.h>

#if FEAT_BUILTIN_EXPORT_FULL
# define EXPORT_USAGE "export [-fn] [name[=value] ...] or export -p"
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
# define EXPORT_HELP "\
Set export attribute for shell variables.\n\
\n\
Marks each NAME for automatic export to the environment of subsequently\n\
executed commands.  If VALUE is supplied, assign VALUE before exporting.\n\
\n\
An argument of `--' disables further option processing.\n\
\n\
Exit Status:\n\
Returns success unless an invalid option is given or NAME is invalid.\n\
"
#endif

void	msh_print_exports(t_minishell *msh, const char *name);
int		msh_export_assign(t_minishell *msh, const char *arg);

static int	msh_builtin_export(int argc, char **argv, t_minishell *msh)
{
	int			i;
	int			ret;

	i = 1;
	ret = 0;
	if (argc == 1)
		msh_print_exports(msh, argv[0]);
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
