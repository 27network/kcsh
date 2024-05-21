/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_free_all.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:45:04 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/21 23:50:36 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/env.h>

void	msh_env_free_all(t_minishell *msh)
{
	t_variable	*tmp;
	t_variable	*next;

	if (!msh->variables)
		return ;
	tmp = msh->variables;
	while (tmp)
	{
		next = tmp->next;
		msh_env_free(tmp);
		tmp = next;
	}
}
