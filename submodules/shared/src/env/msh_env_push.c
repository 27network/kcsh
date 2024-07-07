/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_push.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:20:04 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/07 01:17:43 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/print.h>
#include <ft/string.h>
#include <msh/env.h>

static void	msh_env_update_existing(t_minishell *msh, t_variable *variable,
			const char *value, int flags)
{
	if (!value && (flags & ENV_ALLOC_VALUE))
		ft_dprintf(2, "msh_env_update_existing: value is NULL but flags"
			" suggest it should be allocated\n");
	if (variable->value && variable->flags & ENV_ALLOC_VALUE)
		free(variable->value);
	if (variable->set_fn)
		variable->set_fn(msh, variable, 0, value);
	else
		variable->value = (char *) value;
	variable->flags |= flags;
}

static t_variable	*msh_env_create(t_minishell *msh, const char *key,
						const char *value, int flags)
{
	t_variable	*variable;

	variable = ft_calloc(1, sizeof(t_variable));
	if (!variable)
		return (NULL);
	variable->name = (char *) key;
	msh_env_update_existing(msh, variable, value, flags);
	return (variable);
}

static void	msh_env_insert(t_minishell *msh, t_variable *variable)
{
	t_variable	*root;

	if (!msh->variables)
	{
		msh->variables = variable;
		return ;
	}
	root = msh->variables;
	while (root->next)
		root = root->next;
	root->next = variable;
}

t_variable	*msh_env_push(t_minishell *msh, const char *key, const char *value,
				int flags)
{
	t_variable	*variable;

	if (!key)
		return (NULL);
	variable = msh_env_find(msh, key);
	if (variable)
		msh_env_update_existing(msh, variable, value, flags);
	else
	{
		variable = msh_env_create(msh, key, value, flags);
		if (variable)
			msh_env_insert(msh, variable);
	}
	return (variable);
}
