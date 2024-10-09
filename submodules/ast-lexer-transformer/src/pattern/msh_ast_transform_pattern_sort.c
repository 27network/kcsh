/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_transform_pattern_sort.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 01:47:01 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/09 01:59:39 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/data/list.h>
#include <ft/mem.h>
#include <msh/ast/transformer.h>
#include <msh/util.h>

static void	msh_array_sort(t_minishell *msh, const char **array,
				const size_t size)
{
	size_t		i;
	size_t		j;
	const char	*tmp;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (msh_strcoll(msh, array[i], array[j]) > 0)
			{
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	msh_ast_transform_pattern_sort(t_minishell *msh, t_list **matches)
{
	const size_t	size = ft_lst_size(*matches);
	const char		**array = ft_calloc(size + 1, sizeof(char *));
	t_list			*current;
	size_t			i;

	if (!array)
		return ;
	current = *matches;
	i = 0;
	while (current)
	{
		array[i++] = current->content;
		current = current->next;
	}
	msh_array_sort(msh, array, size);
	current = NULL;
	i = 0;
	while (i < size)
		ft_lst_tadd(&current, (void *) array[i++]);
	free((void *) array);
	ft_lst_free(matches, NULL);
	*matches = current;
}
