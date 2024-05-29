/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin_registry_sort.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 23:19:03 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/29 23:31:21 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <msh/builtin.h>

static void	msh_swap(t_builtin *a, t_builtin *b, size_t size)
{
	t_builtin	tmp;

	ft_memcpy(&tmp, a, size);
	ft_memcpy(a, b, size);
	ft_memcpy(b, &tmp, size);
}

void	msh_builtin_registry_sort(void)
{
	t_builtin	*registry;
	size_t		size;
	size_t		i;
	size_t		min_idx;
	size_t		j;

	registry = msh_builtin_registry();
	size = msh_builtin_count(true);
	i = 0;
	while (i < size - 1)
	{
		min_idx = i;
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(registry[j].name, registry[min_idx].name) < 0)
				min_idx = j;
			j++;
		}
		if (min_idx != i)
			msh_swap(&registry[i], &registry[min_idx], sizeof(t_builtin));
		i++;
	}
}
