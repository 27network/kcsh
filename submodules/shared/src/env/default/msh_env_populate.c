/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_populate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:49:59 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/22 00:24:39 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/env.h>
#include <stdlib.h>

static int	msh_env_create(t_minishell *msh, char *key, char *value)
{
	const int	flags = ENV_ALLOC_NAME | ENV_ALLOC_VALUE
		| ENV_EXPORTED | ENV_IMPORTED;
	t_variable	*variable;

	variable = msh_env_push(msh, key, value, flags);
	if (!variable)
	{
		free(key);
		free(value);
		return (0);
	}
	return (1);
}

static int	msh_env_populate_add(t_minishell *msh, const char *env)
{
	char		*key;
	char		*value;
	char		*value_start;

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
