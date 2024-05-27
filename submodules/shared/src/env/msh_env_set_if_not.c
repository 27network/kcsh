/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_set_if_not.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:33:17 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/26 20:21:24 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/env.h>

t_variable	*msh_env_set_if_not(t_minishell *msh, const char *key,
				const char *value, int flags)
{
	t_variable	*var;

	var = msh_env_find(msh, key);
	if (var == NULL)
		var = msh_env_push(msh, key, value, flags);
	return (var);
}
