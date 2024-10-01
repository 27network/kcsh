/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:47:56 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/01 17:31:08 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/env.h>

char	*msh_env_value(t_minishell *msh, const char *key)
{
	t_variable	*var;

	var = msh_env_find(msh, key);
	if (var)
	{
		if (var->value_fn)
			return (var->value_fn(msh, var, 0, key));
		return (var->value);
	}
	return (NULL);
}
