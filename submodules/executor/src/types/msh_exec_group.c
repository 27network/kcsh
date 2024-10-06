/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_group.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 20:30:04 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/06 20:42:43 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <msh/exec.h>
#include <msh/features.h>
#include <msh/log.h>

int		msh_restore_fds(t_minishell *msh, int fds[3]);
int		msh_save_fds(t_minishell *msh, int fds[3]);

// Rely on the command execution system
int		msh_exec_command_dispatch(t_exec_state *state, t_ast_node *node,
			bool do_fork, pid_t pid);

static int	msh_exec_group_setup(t_exec_state *state, t_ast_node *node)
{
	const t_ast_token	*tkn = (const t_ast_token *) node->group.group->content;
	const bool			do_fork = (tkn->kind == GROUP_SUBSHELL
			&& FEAT_SUBSHELLS);
	int					fds[3];
	pid_t				pid;
	int					ret;

	ret = 0;
	pid = -1;
	ft_bzero(fds, sizeof(fds));
	if (do_fork)
	{
		pid = msh_fork(state->msh);
		if (pid == -1)
			return (1);
	}
	else if (!msh_save_fds(state->msh, fds))
		return (1);
	ret = msh_exec_command_dispatch(state, node, do_fork, pid);
	if (pid != 0 && !do_fork && !msh_restore_fds(state->msh, fds))
		return (1);
	return (ret);
}

int	msh_exec_group(t_exec_state *state, t_ast_node *node)
{
	const t_list	*token = node->group.tokens;
	t_ast_token		*t;
	int				ret;

	ret = 0;
	t = NULL;
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
