/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouchet <ebouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 23:07:57 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/09 12:53:10 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/builtin.h>
#include <msh/env.h>
#include <stdio.h>
#include <ft/mem.h>

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

static int	msh_export_error(t_minishell *msh, const char *data, int errtype)
{
	if (errtype == 1)
		msh_error(msh, "export: `%s' is not a valid identifier\n", data);
	else if (errtype == 2)
		msh_error(msh, "export: name allocation error\n");
	else if (errtype == 3)
		msh_error(msh, "export: value allocation error\n");
	else if (errtype == 4)
		msh_error(msh, "export: env allocation error\n");
	else
		msh_error(msh, "export: unknown error\n");
	return (1);
}
/*
static void	msh_env_get_name2(char *argv, char *sep, char *name, t_minishell *msh)
{
	bool	plus;

	plus = (*sep == '+');
	if (plus)
		sep++;			// sep="=jweoifjw"
	if (*sep != '=')
		msh_export_error();
	else
		sep++;			// sep="jweoifjw"
	if (!plus)
		msh_env_push(msh, name, ft_strdup(sep), ENV_EXPORTED | ENV_VALUE_ALLOC);
	else
	{
		char *value = msh_env_value(msh, name);
		value = ft_strcat(value, sep);
		msh_env_push(msh, name, value, ENV_EXPORTED)
	}
}*/

static int	msh_env_get_name(t_minishell *msh, const char *argv) // name=value name+=value name
{
	char	*name;
	char	*sep;
	size_t	name_size;
	bool	plus;
	char	*value;
	t_variable	*new;

	sep = ft_strpbrk(argv, "+="); // sep="+=jweoifjw"
	if (!sep)
	{
		if (!msh_env_is_valid_name(argv, true))
			return (msh_export_error(msh, argv, 1));
		new = msh_env_get(msh, argv, 0);
		if (!new)
			return (msh_export_error(msh, NULL, 4));
		new->flags |= ENV_EXPORTED;
		return (0);
	}
	name_size = sep - argv;
	name = ft_strndup(argv, name_size);
	if (!name)
		return (msh_export_error(msh, NULL, 2));
	if (!msh_env_is_valid_name(name, true))
		return (msh_export_error(msh, argv, 1)); //faire error
	plus = (*sep == '+');
	if (plus)
		sep++;			// sep="=jweoifjw"
	if (*sep != '=')
		return (msh_export_error(msh, argv, 1));
	sep++;			// sep="jweoifjw"
	if (!plus)
		msh_env_push(msh, name, ft_strdup(sep), ENV_EXPORTED | ENV_ALLOC_NAME | ENV_ALLOC_VALUE);
	else
	{
		value = msh_env_value(msh, name);
		value = ft_calloc(ft_strlen(value) + ft_strlen(sep) + 1, 1);
		if (!value)
			return (msh_export_error(msh, NULL, 3));
		ft_strcat(value, name);
		ft_strcat(value, sep);
		msh_env_push(msh, name, value, ENV_EXPORTED | ENV_ALLOC_NAME | ENV_ALLOC_VALUE);
	}
	return (0);
}

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
			printf("test '%s'\n", argv[1]);
			if (msh_env_get_name(msh, argv[i]))
				ret = 1;
			i++;
		}
		// export name[[+]=value]
		// export name=value name+=value
		// export PTDR -> PTDR=null
		// export PTDR= -> PTDR=""
		// export PTDR=A -> PTDR="A"
		// export PTDR+=B -> PTDR="AB"
		// export VALID=A 0INVALID=B VALID2=C -> VALID="A" VALID2="C"
	}
	return (ret);
}

__attribute__((constructor))
void	register_export(void)
{
	msh_builtin_register((t_builtin){
		.name = "export",
		.usage = USAGE_EXPORT,
		.help = HELP_EXPORT,
		.func = msh_builtin_export,
		.flags = BUILTIN_NEEDS_MSH | BUILTIN_SPECIAL,
	});
}
