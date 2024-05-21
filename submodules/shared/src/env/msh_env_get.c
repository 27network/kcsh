/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:14:24 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/21 19:00:38 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/env.h>

t_variable	*msh_env_get(t_minishell *msh, const char *key, int flags)
{
	t_variable	*variable;

	variable = msh_env_find(msh, key);
	if (!variable)
		variable = msh_env_push(msh, key, NULL, flags);
	return (variable);
}
