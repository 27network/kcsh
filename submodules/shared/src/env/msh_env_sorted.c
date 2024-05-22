/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_sorted.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 01:37:28 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/22 03:11:45 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <msh/env.h>
#include <msh/log.h>

static size_t	msh_env_size(t_minishell *msh)
{
	size_t		size;
	t_variable	*var;

	size = 0;
	var = msh->variables;
	while (var)
	{
		size++;
		var = var->next;
	}
	return (size);
}

static void	msh_env_copy(t_minishell *msh, t_variable *new, size_t size)
{
	t_variable	*var;
	size_t		i;

	i = 0;
	var = msh->variables;
	while (var && i < size)
	{
		new[i] = *var;
		var = var->next;
		i++;
	}
}

static void	msh_env_sort(t_variable *new, size_t size)
{
	size_t		i;
	size_t		j;
	t_variable	tmp;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(new[i].name, new[j].name) < 0)
			{
				tmp = new[i];
				new[i] = new[j];
				new[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static t_variable	*msh_env_array_to_list(t_variable *new)
{
	t_variable	*root;
	t_variable	*tmp;
	size_t		i;

	i = 0;
	root = NULL;
	while (new[i].name)
	{
		tmp = ft_calloc(1, sizeof(t_variable));
		if (!tmp)
			return (NULL);
		*tmp = new[i];
		tmp->flags |= ENV_COPIED;
		tmp->next = root;
		root = tmp;
		i++;
	}
	return (root);
}

t_variable	*msh_env_sorted(t_minishell *msh)
{
	t_variable	*new;
	t_variable	*linked;
	size_t		size;

	size = msh_env_size(msh);
	new = ft_calloc(size + 1, sizeof(t_variable));
	if (!new)
		msh_error(msh, "msh_env_sorted: ft_calloc failed\n");
	if (!new)
		return (NULL);
	msh_env_copy(msh, new, size);
	msh_env_sort(new, size);
	linked = msh_env_array_to_list(new);
	free(new);
	if (!linked)
		msh_error(msh, "msh_env_sorted: msh_env_array_to_list failed\n");
	return (linked);
}
