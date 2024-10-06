/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_delim_async.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 22:34:48 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/05 00:40:32 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/exec.h>

void	msh_update_env(t_minishell *msh, bool update_lineno);

int	msh_exec_delim_async(t_exec_state *state, t_ast_node *node)
{
	int	ret;

	ret = 0;
	(void) state;
	(void) node;
	return (ret);
}
