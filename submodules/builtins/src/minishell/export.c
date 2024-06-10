/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 23:07:57 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/06 11:59:51 by kiroussa         ###   ########.fr       */
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

//TODO: replace with shell flag
#define POSIX 0

static size_t	msh_variable_flags(t_variable *var, char *flags)
{
	size_t	nflags;

	nflags = 0;
	if (var->flags & ENV_ARRAY)
		flags[nflags++] = 'a';
	if (var->flags & ENV_ASSOC)
		flags[nflags++] = 'A';
	if (var->flags & ENV_FUNCTION)
		flags[nflags++] = 'f';
	if (!POSIX)
	{
		if (var->flags & ENV_INTEGER)
			flags[nflags++] = 'i';
		if (var->flags & ENV_READONLY)
			flags[nflags++] = 'r';
		if (var->flags & ENV_EXPORTED)
			flags[nflags++] = 'x';
	}
	flags[nflags] = 0;
	return (nflags);
}

static void	msh_print_export_declaration(t_minishell *msh, char *argv0,
				t_variable *var)
{
	char	flags[32];
	size_t	nflags;

	nflags = msh_variable_flags(var, flags);
	if (!POSIX)
		printf("declare -%s ", flags);
	else if (nflags)
		printf("%s -%s ", argv0, flags);
	else
		printf("%s ", argv0);
	//TODO: proper ANSI-C quoting for escaping function declarations
	msh_env_print_assignment(msh, var, 1);
}

static void	msh_print_exports(t_minishell *msh, char *argv0)
{
	t_variable	*root;
	t_variable	*tmp;

	root = msh_env_sorted(msh);
	if (!root)
		msh_error(msh, "msh_print_exports: msh_env_sorted failed\n");
	if (!root)
		return ;
	while (root)
	{
		if (root->value && (root->flags & ENV_EXPORTED))
			msh_print_export_declaration(msh, argv0, root);
		tmp = root;
		root = root->next;
		msh_env_free(tmp);
	}
}

static int	msh_builtin_export(int argc, char **argv, t_minishell *msh)
{
	if (argc == 1)
		msh_print_exports(msh, argv[0]);
	(void) argv;
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
