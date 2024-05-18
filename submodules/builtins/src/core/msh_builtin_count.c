/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 03:02:21 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/17 03:03:17 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/builtin.h>

size_t	msh_builtin_count(void)
{
	size_t		i;
	t_builtin	*g_builtin;

	i = 0;
	g_builtin = msh_builtin_registry();
	while (i < BUILTIN_REGISTRY_SIZE && g_builtin[i].name)
		i++;
	return (i);
}
