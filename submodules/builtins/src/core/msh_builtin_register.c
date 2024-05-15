/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin_register.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 23:04:42 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/15 23:14:48 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <msh/builtin.h>
#include <stdbool.h>
#include <stdlib.h>

static void	msh_builtin_check(t_builtin *builtin)
{
	if (!builtin->name)
		ft_dprintf(2, "builtin registry: builtin name is NULL\n");
	if (!builtin->func)
		ft_dprintf(2, "builtin registry: func for %s is NULL\n",
			builtin->name);
	if (!builtin->usage || !builtin->help)
		ft_dprintf(2, "builtin registry: usage or help for %s is NULL\n",
			builtin->name);
	if (!(builtin->func && builtin->name))
		exit(-2);
}

void	msh_builtin_register(t_builtin builtin)
{
	t_builtin	*builtins;
	size_t		i;

	msh_builtin_check(&builtin);
	builtins = msh_builtin_registry();
	i = 0;
	while (i < BUILTIN_REGISTRY_SIZE)
	{
		if (!builtins[i].name)
		{
			builtins[i] = builtin;
			return ;
		}
		i++;
	}
	ft_dprintf(2, "builtin registry: too many builtins registered, "
		"max is %d\n", BUILTIN_REGISTRY_SIZE);
	exit(-1);
}
