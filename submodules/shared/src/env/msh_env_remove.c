/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouchet <ebouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 12:57:32 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/09 13:09:04 by ebouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/env.h>

void	msh_env_remove(t_minishell *msh, const char *name)
{
	t_variable	*root;
	t_variable	*prev;

	root = msh->variables;
	prev = NULL;
	while (root)
	{
		if (!ft_strcmp(root->name, name))
		{
			if (prev)
				prev->next = root->next;
			else
				msh->variables = root->next;
			msh_env_free(root);
			return ;
		}
		prev = root;
		root = root->next;
	}
}
