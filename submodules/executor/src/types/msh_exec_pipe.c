/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 03:07:59 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/09 03:08:03 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/exec.h>

static int	msh_exec_pipe(t_exec_state *state, t_ast_node *node)
{
	t_ast_node	*left;
	t_ast_node	*right;

	left = node->left;
	right = node->right;
	if (left->type == NODE_COMMAND)
		return (msh_exec_command(state, left));
	if (right->type == NODE_COMMAND)
		return (msh_exec_command(state, right));
	return (0);
}
