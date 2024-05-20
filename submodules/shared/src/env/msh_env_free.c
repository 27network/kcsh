/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:46:23 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/20 15:53:27 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/env.h>
#include <stdlib.h>

void	msh_env_free(t_variable *variable)
{
	if (variable->flags & ENV_FLAG_ALLOC_NAME && variable->key)
		free(variable->key);
	if (variable->flags & ENV_FLAG_ALLOC_VALUE && variable->value)
		free(variable->value);
	free(variable);
}
