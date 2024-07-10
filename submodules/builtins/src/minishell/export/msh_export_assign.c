/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export_assign.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouchet <ebouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:51:14 by ebouchet          #+#    #+#             */
/*   Updated: 2024/07/10 06:50:16 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/env.h>
#include <ft/mem.h>
#include <ft/string.h>
#include <msh/log.h>

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

static int	msh_env_handle_no_separator(t_minishell *msh, const char *argv)
{
	t_variable	*new;

	if (!msh_env_is_valid_name(argv, true))
		return (msh_export_error(msh, argv, 1));
	new = msh_env_get(msh, argv, 0);
	if (!new)
		return (msh_export_error(msh, NULL, 4));
	new->flags |= ENV_EXPORTED;
	return (0);
}

static int	msh_env_handle_separator(t_minishell *msh, char *name, char *sep,
				bool plus)
{
	char	*value;

	if (!plus)
	{
		msh_env_push(msh, name, ft_strdup(sep), ENV_EXPORTED | ENV_ALLOC_NAME
			| ENV_ALLOC_VALUE);
		return (0);
	}
	value = msh_env_value(msh, name);
	value = ft_calloc(ft_strlen(value) + ft_strlen(sep) + 1, 1);
	if (!value)
		return (msh_export_error(msh, NULL, 3));
	ft_strcat(value, name);
	ft_strcat(value, sep);
	msh_env_push(msh, name, value, ENV_EXPORTED | ENV_ALLOC_NAME
		| ENV_ALLOC_VALUE);
	return (0);
}

int	msh_export_assign(t_minishell *msh, const char *argv,
		bool func, bool negate)
{
	char	*name;
	char	*sep;
	size_t	name_size;
	bool	plus;

	(void) func;
	(void) negate;
	sep = ft_strpbrk(argv, "+=");
	if (!sep)
		return (msh_env_handle_no_separator(msh, argv));
	name_size = sep - argv;
	name = ft_strndup(argv, name_size);
	if (!name)
		return (msh_export_error(msh, NULL, 2));
	if (!msh_env_is_valid_name(name, true))
		return (msh_export_error(msh, argv, 1));
	plus = (*sep == '+');
	if (plus)
		sep++;
	if (*sep != '=')
		return (msh_export_error(msh, argv, 1));
	sep++;
	return (msh_env_handle_separator(msh, name, sep, plus));
}
