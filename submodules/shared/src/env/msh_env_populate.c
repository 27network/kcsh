/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_populate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:49:59 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/21 01:54:50 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/env.h>
#include <stdlib.h>

static int	msh_env_create(t_minishell *msh, char *key, char *value)
{
	t_variable	*variable;

	variable = msh_env_get_or_create(msh, key);
	if (!variable)
	{
		free(key);
		free(value);
		return (0);
	}
	if (variable->name && variable->flags & ENV_ALLOC_NAME)
		free(variable->name);
	if (variable->value && variable->flags & ENV_ALLOC_VALUE)
		free(variable->value);
	variable->flags |= ENV_ALLOC_NAME | ENV_ALLOC_VALUE | ENV_EXPORTED
		| ENV_IMPORTED;
	variable->name = key;
	variable->value = value;
	return (1);
}

static int	msh_env_populate_add(t_minishell *msh, const char *env)
{
	char		*key;
	char		*value;
	char		*value_start;
	t_variable	*variable;

	value_start = ft_strchr(env, '=');
	if (!value_start)
		return (0);
	key = ft_strndup(env, value_start - env);
	if (!key)
		return (0);
	value = ft_strdup(value_start + 1);
	if (!value)
	{
		free(key);
		return (0);
	}
	return (msh_env_create(msh, key, value));
}

int	msh_env_populate(t_minishell *msh, const char **envp)
{
	size_t		i;

	i = 0;
	while (envp[i])
	{
		if (!msh_env_populate_add(msh, envp[i]))
			return (0);
		i++;
	}
	return (1);
}
