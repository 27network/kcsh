/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:46:23 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/22 03:00:50 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/env.h>
#include <stdlib.h>

void	msh_env_free(t_variable *variable)
{
	if (!(variable->flags & ENV_COPIED))
	{
		if (variable->flags & ENV_ALLOC_NAME && variable->name)
			free(variable->name);
		if (variable->flags & ENV_ALLOC_VALUE && variable->value)
			free(variable->value);
	}
	free(variable);
}
