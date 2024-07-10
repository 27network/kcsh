/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouchet <ebouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:14:24 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/10 14:40:02 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/env.h>
#include <stdlib.h>

t_variable	*msh_env_get(t_minishell *msh, const char *key, int flags)
{
	t_variable	*variable;

	if (!key)
		return (NULL);
	if (flags & ENV_ALLOC_NAME)
		key = ft_strdup(key);
	variable = msh_env_find(msh, key);
	if (!variable)
		variable = msh_env_push(msh, key, NULL,
				flags);
	else if (flags & ENV_ALLOC_NAME)
		free((char *) key);
	return (variable);
}
