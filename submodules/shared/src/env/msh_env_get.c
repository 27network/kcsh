/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:58:05 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/20 15:31:37 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/env.h>

t_variable	*msh_env_get(t_minishell *msh, const char *key)
{
	t_variable	*root;

	root = msh->variables;
	while (root)
	{
		if (ft_strcmp(root->key, key) == 0)
			return (root);
		root = root->next;
	}
	return (NULL);
}
