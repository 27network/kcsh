/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_group.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 20:30:04 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/06 00:32:07 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/exec.h>
#include <msh/log.h>

static int	msh_exec_group_setup(t_exec_state *state, t_ast_node *node)
{
	(void)state;
	(void)node;
	// pid_t	pid;
	// int		ret;
	//
	// ret = 0;
	// pid = msh_fork(state->msh);
	// if (pid == -1)
	// 	return (1);
	// else if (pid == 0)
	// {
	// 	msh_signal_setdfl();
	// }
	// return (ret);
	return (0);
}

int	msh_exec_group(t_exec_state *state, t_ast_node *node)
{
	const t_list	*token = node->group.tokens;
	t_ast_token		*t;
	int				ret;

	ret = 0;
	while (token)
	{
		t = (t_ast_token *) token->content;
		if (t->type == TKN_REDIR && !ft_lst_tadd(&node->group.redirs, t))
			ret = 1;
		token = token->next;
	}
	if (ret)
		msh_error(state->msh, "failed to prepare group (malloc error)\n");
	else
		msh_log(state->msh, MSG_DEBUG_EXECUTOR, "Group setup\n");
	if (!ret)
		ret = msh_exec_group_setup(state, node);
	msh_log(state->msh, MSG_DEBUG_EXECUTOR, "Group setup done %d\n", ret);
	ft_lst_free(&node->group.redirs, NULL);
	return (ret);
}
