/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_delim.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 07:11:41 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/05 00:57:05 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/exec.h>

int	msh_exec_delim_async(t_exec_state *state, t_ast_node *node);
int	msh_exec_delim_and(t_exec_state *state, t_ast_node *node);
int	msh_exec_delim_or(t_exec_state *state, t_ast_node *node);
int	msh_exec_delim_semicolon(t_exec_state *state, t_ast_node *node);

__attribute__((always_inline))
static inline int	msh_delim_check_prerequisites(t_ast_node *node)
{
	const t_ast_delim_type	delim = node->delim;
	const bool				req_right = delim == DELIM_AND || delim == DELIM_OR;

	if (req_right && node->right == NULL)
		return (1);
	if (node->left == NULL)
		return (1);
	return (0);
}

int	msh_exec_delim(t_exec_state *state, t_ast_node *node)
{
	const t_ast_delim_type	delim = node->delim;
	int						ret;

	ret = msh_delim_check_prerequisites(node);
	if (ret != 0)
		return (ret);
	if (delim == DELIM_ASYNC)
		return (msh_exec_delim_async(state, node));
	else if (delim == DELIM_AND)
		return (msh_exec_delim_and(state, node));
	else if (delim == DELIM_OR)
		return (msh_exec_delim_or(state, node));
	else if (delim == DELIM_SEMICOLON)
		return (msh_exec_delim_semicolon(state, node));
	return (0);
}
