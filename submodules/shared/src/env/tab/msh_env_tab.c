/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:24:05 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/22 00:18:18 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <ft/mem.h>
#include <ft/print.h>
#include <msh/env.h>
#include <msh/log.h>

static size_t	msh_env_size_for(t_minishell *msh, int match_flags)
{
	size_t		size;
	t_variable	*root;

	size = 0;
	root = msh->variables;
	while (root)
	{
		if ((root->flags & match_flags) == match_flags && root->value)
			size++;
		root = root->next;
	}
	return (size);
}

static char	**msh_env_tab_error(t_minishell *msh, char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	msh_error(msh, "couldn't build variables tab (inner)");
	return (NULL);
}

char	**msh_env_tab(t_minishell *msh, int match_flags)
{
	size_t		i;
	char		**array;
	t_variable	*root;

	array = ft_calloc(msh_env_size_for(msh, match_flags) + 1, sizeof(char *));
	if (!array)
		msh_error(msh, "couldn't build variables tab");
	if (!array)
		return (ft_calloc(1, sizeof(char *)));
	root = msh->variables;
	i = 0;
	while (root)
	{
		if ((root->flags & match_flags) == match_flags && root->value)
		{
			array[i] = ft_strjoins(2, "=", 0b00, root->name, root->value);
			if (!array[i])
				return (msh_env_tab_error(msh, array));
			i++;
		}
		root = root->next;
	}
	return (array);
}
