/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:24:05 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/20 16:11:04 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/print.h>
#include <msh/env.h>
#include <msh/log.h>

static size_t	msh_env_exportable_size(t_minishell *msh)
{
	size_t		size;
	t_variable	*root;

	size = 0;
	root = msh->variables;
	while (root)
	{
		if (msh_env_is_flag(root, ENV_EXPORTABLE))
			size++;
		root = root->next;
	}
	return (size);
}

static char	*msh_env_tab_error(t_minishell *msh, char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	msh_error(msh, "couldn't build environment tab");
	return (NULL);
}

char	**msh_env_tab(t_minishell *msh)
{
	size_t		i;
	char		**array;
	t_variable	*root;

	array = ft_calloc(msh_env_exportable_size(msh) + 1, sizeof(char *));
	if (!array)
		msh_error(msh, "couldn't build environment tab");
	if (!array)
		return (ft_calloc(1, sizeof(char *)));
	root = msh->variables;
	i = 0;
	while (root)
	{
		if (msh_env_is_flag(root, ENV_EXPORTABLE))
		{
			array[i] = ft_strjoins(2, "=", 0b00, root->key, root->value);
			if (!array[i])
				return (msh_env_tab_error(msh, array));
			i++;
		}
		root = root->next;
	}
	return (array);
}
