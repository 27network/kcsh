/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_push.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:20:04 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/21 17:47:58 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/env.h>

// char *newshlvl = itoa(shlvl + 1)
// push("SHLVL", newshlvl, ENV_ALLOC_VALUE | ENV_EXPORTED);

static void	msh_env_update_existing(t_variable *variable,
			const char *value, int flags)
{
	if (!value && (flags & ENV_ALLOC_VALUE))
		ft_dprintf(2, "msh_env_update_existing: value is NULL but flags"
			" suggest it should be allocated\n");
	if (variable->value && variable->flags & ENV_ALLOC_VALUE)
		free(variable->value);
	if (flags & ENV_ALLOC_VALUE)
		variable->flags |= ENV_ALLOC_VALUE;
	if (flags & ENV_EXPORTED)
		variable->flags |= ENV_EXPORTED;
}

t_variable	*msh_env_push(t_minishell *msh, const char *key, const char *value,
				int flags)
{
	t_variable	*variable;

	variable = msh_env_find(msh, key);
	if (variable)
		msh_env_update_existing(variable, value, flags);
	else
	{
		variable = msh_env_create(key, value, flags);
		if (variable)
			msh_env_insert_sorted(msh, variable);
	}
	return (variable);
}
