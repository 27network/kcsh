/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouchet <ebouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 23:07:57 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/28 18:57:55 by ebouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/builtin.h>
#include <msh/env.h>
#include <stdio.h>

#if FEAT_BUILTIN_EXPORT_FULL
# define USAGE_EXPORT "export [-fn] [name[=value] ...] or export -p"
# define HELP_EXPORT "\
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
# define USAGE_EXPORT "export [name[=value]]"
# define HELP_EXPORT "\
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

static int	msh_builtin_export(int argc, char **argv, t_minishell *msh)
{
	if (argc == 1)
		msh_print_exports(msh, argv[0]);
	else
	{
		// export name[[+]=value]
		//		  name name=value name+=value
		// export PTDR -> PTDR=null
		// export PTDR= -> PTDR=""
		// export PTDR=A -> PTDR="A"
		// export PTDR+=B -> PTDR="AB"
		// export VALID=A 0INVALID=B VALID2=C -> VALID="A" VALID2="C"
		(void) argv;
	}
	return (0);
}

__attribute__((constructor))
void	register_export(void)
{
	msh_builtin_register((t_builtin){
		.name = "export",
		.usage = USAGE_EXPORT,
		.help = HELP_EXPORT,
		.func = msh_builtin_export,
		.needs = NEEDS_MSH,
		.enabled = true,
	});
}
