/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 03:07:59 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/13 17:35:53 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/exec.h>

int	msh_exec_pipe(t_exec_state *state, t_ast_node *node)
{
	t_ast_node	*left;
	t_ast_node	*right;
	int			ret;
	bool		pipe_state;

	left = node->left;
	right = node->right;
	ret = msh_exec(state, left);
	if (ret != 0)
		return (ret);
	pipe_state = state->is_in_pipe;
	state->is_in_pipe = true;
	ret = msh_exec(state, right);
	state->is_in_pipe = pipe_state;
	return (ret);
}
