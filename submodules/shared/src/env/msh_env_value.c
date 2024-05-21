/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:47:56 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/21 23:59:56 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/env.h>

char	*msh_env_value(t_minishell *msh, const char *key)
{
	t_variable	*var;

	var = msh_env_find(msh, key);
	if (var)
	{
		if (var->fn)
			return (var->fn(msh, var));
		return (var->value);
	}
	return (NULL);
}
