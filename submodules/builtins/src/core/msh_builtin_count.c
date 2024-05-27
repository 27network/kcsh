/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 03:02:21 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/27 05:10:53 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/builtin.h>

size_t	msh_builtin_count(bool include_hidden)
{
	size_t		i;
	size_t		count;
	t_builtin	*g_builtin;

	i = 0;
	count = 0;
	g_builtin = msh_builtin_registry();
	while (i < BUILTIN_REGISTRY_SIZE && g_builtin[i].name)
	{
		if (include_hidden || !(g_builtin[i].hidden))
			count++;
		i++;
	}
	return (count);
}
