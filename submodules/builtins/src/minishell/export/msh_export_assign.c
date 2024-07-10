/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export_assign.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouchet <ebouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:51:14 by ebouchet          #+#    #+#             */
/*   Updated: 2024/07/10 10:07:42 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/env.h>
#include <ft/mem.h>
#include <ft/string.h>
#include <msh/log.h>

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
		*name = sep;
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

static int	msh_export_update(t_variable *variable, char *value, bool plus, bool negate)
{
	(void)negate;
	(void)plus;
	(void)value;
	(void)variable;
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
	variable = msh_env_get(msh, name, 0);
	ft_strdel(&name);
	if (!variable)
		ft_strdel(&value);
	if (!variable)
		return (msh_export_error(msh, argv, ENV_ALLOC_ERROR));
	if (func && !(variable->flags & ENV_FUNCTION))
		ft_strdel(&value);
	if (func && !(variable->flags & ENV_FUNCTION))
		return (msh_export_error(msh, argv, NOT_FUNCTION_ERROR));
	return (msh_export_update(variable, value, plus, negate));
}
