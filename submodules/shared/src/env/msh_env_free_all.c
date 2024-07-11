/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_free_all.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouchet <ebouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:45:04 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/11 16:27:43 by ebouchet         ###   ########.fr       */
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
		msh_env_free(msh, tmp);
		tmp = next;
	}
}
