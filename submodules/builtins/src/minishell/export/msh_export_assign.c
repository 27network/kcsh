/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export_assign.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouchet <ebouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:51:14 by ebouchet          #+#    #+#             */
/*   Updated: 2024/07/10 14:56:43 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <msh/env.h>
#include <msh/log.h>
#include <stdlib.h>

#define INVALID_IDENTIFIER_ERROR 1
#define NAME_ALLOC_ERROR 2
#define VALUE_ALLOC_ERROR 3
#define ENV_ALLOC_ERROR 4
#define NOT_FUNCTION_ERROR 5
#define UNKNOWN_ERROR -1

void	msh_env_update_existing(t_minishell *msh, t_variable *variable,
			const char *value, int flags);

static int	msh_export_error(t_minishell *msh, const char *data, int errtype)
{
	if (errtype == INVALID_IDENTIFIER_ERROR)
		msh_error(msh, "export: `%s': not a valid identifier\n", data);
	else if (errtype == NAME_ALLOC_ERROR)
		msh_error(msh, "export: name allocation error\n");
	else if (errtype == VALUE_ALLOC_ERROR)
		msh_error(msh, "export: value allocation error\n");
	else if (errtype == ENV_ALLOC_ERROR)
		msh_error(msh, "export: env allocation error\n");
	else if (errtype == NOT_FUNCTION_ERROR)
		msh_error(msh, "export: `%s': not a function\n", data);
	else
		msh_error(msh, "export: unknown error\n");
	return (1);
}

static int	msh_export_parse(const char *arg, char **name,
				char **value, bool *plus)
{
	char	*sep;

	sep = ft_strpbrk(arg, "+=");
	*plus = (sep && *sep == '+');
	*value = NULL;
	if (!sep)
	{
		*name = ft_strdup(arg);
		if (!*name)
			return (NAME_ALLOC_ERROR);
		return (0);
	}
	*name = ft_strndup(arg, sep - arg);
	if (!*name)
		return (NAME_ALLOC_ERROR);
	if (*plus)
		sep++;
	if (*sep != '=')
		return (1);
	if (!msh_env_is_valid_name(*name, true))
		return (INVALID_IDENTIFIER_ERROR);
	*value = ft_strdup(sep + 1);
	if (!*value)
		return (VALUE_ALLOC_ERROR);
	return (0);
}

#define FLAG_NEGATE 1
#define FLAG_PLUS 2

static int	msh_export_update(t_minishell *msh, t_variable *variable,
				const char *value, int export_flags)
{
	const bool	negate = (export_flags & FLAG_NEGATE);
	const bool	plus = (export_flags & FLAG_PLUS);
	char		*new_value;

	variable->flags |= ENV_EXPORTED;
	if (negate)
		variable->flags &= ~(ENV_EXPORTED);
	if (!value)
		return (0);
	if (!plus)
		msh_env_update_existing(msh, variable, value, ENV_ALLOC_VALUE);
	else
	{
		new_value = ft_strnew(ft_strlen(variable->value) + ft_strlen(value));
		if (!new_value)
			return (msh_export_error(msh, NULL, VALUE_ALLOC_ERROR));
		if (variable->value)
			ft_strcat(new_value, variable->value);
		ft_strcat(new_value, value);
		free((void *) value);
		msh_env_update_existing(msh, variable, new_value, ENV_ALLOC_VALUE);
	}
	return (0);
}

int	msh_export_assign(t_minishell *msh, const char *argv,
		bool func, bool negate)
{
	char		*name;
	char		*value;
	bool		plus;
	int			ret;
	t_variable	*variable;

	ret = msh_export_parse(argv, &name, &value, &plus);
	if (ret)
	{
		ft_strdel(&name);
		ft_strdel(&value);
		return (msh_export_error(msh, argv, ret));
	}
	variable = msh_env_get(msh, name, ENV_ALLOC_NAME);
	ft_strdel(&name);
	if (!variable)
		ft_strdel(&value);
	if (!variable)
		return (msh_export_error(msh, argv, ENV_ALLOC_ERROR));
	if (func && !(variable->flags & ENV_FUNCTION))
		ft_strdel(&value);
	if (func && !(variable->flags & ENV_FUNCTION))
		return (msh_export_error(msh, argv, NOT_FUNCTION_ERROR));
	return (msh_export_update(msh, variable, value,
			plus * FLAG_PLUS | negate * FLAG_NEGATE));
}
