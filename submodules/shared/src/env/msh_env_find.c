/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:58:05 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/21 23:50:21 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/env.h>

t_variable	*msh_env_find(t_minishell *msh, const char *key)
{
	t_variable	*root;

	root = msh->variables;
	while (root)
	{
		if (ft_strcmp(root->name, key) == 0)
			return (root);
		root = root->next;
	}
	return (NULL);
}
