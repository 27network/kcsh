/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouchet <ebouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:14:24 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/09 11:54:12 by ebouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/env.h>

t_variable	*msh_env_get(t_minishell *msh, const char *key, int flags)
{
	t_variable	*variable;

	variable = msh_env_find(msh, key);
	if (!variable)
		variable = msh_env_push(msh, ft_strdup(key), NULL,
			flags | ENV_ALLOC_NAME);
	return (variable);
}
