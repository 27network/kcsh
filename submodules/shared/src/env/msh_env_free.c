/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouchet <ebouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:46:23 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/01 17:13:48 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/env.h>
#include <msh/log.h>
#include <stdlib.h>

void	msh_env_free(t_minishell *msh, t_variable *variable)
{
	const bool	log = !msh->forked;

	if (!(variable->flags & ENV_COPIED))
	{
		if (log)
			msh_log(msh, MSG_DEBUG_GENERIC, "Freeing variable %s=%s\n",
				variable->name, variable->value);
		if (variable->flags & ENV_ALLOC_NAME && variable->name)
		{
			if (log)
				msh_log(msh, MSG_DEBUG_GENERIC, "\tfreeing name\n");
			ft_strdel(&variable->name);
		}
		if (variable->flags & ENV_ALLOC_VALUE && variable->value)
		{
			if (log)
				msh_log(msh, MSG_DEBUG_GENERIC, "\tfreeing value\n");
			ft_strdel(&variable->value);
		}
	}
	free(variable);
}
