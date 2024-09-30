/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 01:51:37 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/30 08:58:15 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <ft/data/list.h>
#include <msh/ast/transformer.h>
#include <msh/exec.h>
#include <msh/signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

void	msh_dump_tokens(t_minishell *msh, t_list *tokens);
t_list	*msh_clone_tokens(t_minishell *msh, t_list *tokens);

int		msh_restore_fds(t_minishell *msh, int fds[2]);
int		msh_save_fds(t_minishell *msh, int fds[2]);

bool	msh_exec_command_not_builtin(t_ast_node *node);
int		msh_exec_status(int wait_status);
int		msh_exec_command_redirections(t_exec_state *state,
			t_ast_node *node);

#define TODO_42SH 0

static int	msh_exec_command_dispatch(t_exec_state *state, t_ast_node *node,
				bool do_fork, pid_t pid)
{
	const bool	interactive = state->msh->interactive;
	int			status;

	if (!do_fork)
		return (msh_exec_command_redirections(state, node));
	if (pid == 0)
	{
		state->msh->execution_context.running = false;
		msh_signal_setdfl();
		return (msh_exec_command_redirections(state, node));
	}
	if (node->command.background)
		return (TODO_42SH);
	state->msh->interactive = false;
	msh_signal_init(state->msh, false);
	if (waitpid(pid, &status, 0) == -1 && (errno != EINTR && errno != ECHILD))
	{
		msh_error(state->msh, "failed to wait for pid %d\n", pid);
		return (1);
	}
	state->msh->interactive = interactive;
	msh_signal_init(state->msh, false);
	return (msh_exec_status(status));
}

static int	msh_exec_command_setup(t_exec_state *state, t_ast_node *node)
{
	const bool		do_fork = state->depth == 1
		&& msh_exec_command_not_builtin(node);
	pid_t			pid;
	int				fds[2];
	int				ret;

	ret = 0;
	pid = -1;
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

static int	msh_exec_command_prepare(t_exec_state *state, t_ast_node *node)
{
	const t_list	*token = node->command.tokens;
	t_ast_token		*t;
	int				error;

	error = false;
	while (token && !error)
	{
		t = (t_ast_token *) token->content;
		if (t->type == TKN_REDIR && !ft_lst_tadd(&node->command.redirs, t))
			error = true;
		else if (t->type == TKN_WORD && !ft_lst_tadd(&node->command.args, t))
			error = true;
		token = token->next;
	}
	if (error)
		msh_error(state->msh, "failed to prepare command (memalloc?)\n");
	else
		msh_log(state->msh, MSG_DEBUG_EXECUTOR, "Command setup\n");
	if (!error)
		error = msh_exec_command_setup(state, node);
	ft_lst_free(&node->command.redirs, NULL);
	ft_lst_free(&node->command.args, NULL);
	ft_lst_free(&node->command.env, NULL);
	return (error);
}

int	msh_exec_command(
	t_exec_state *state,
	t_ast_node *node
) {
	t_ast_error	err;
	t_list		*cloned;
	t_list		*backup;
	int			ret;

	cloned = msh_clone_tokens(state->msh, node->command.tokens);
	if (!cloned)
		return (1);
	err = msh_ast_transform(state->msh, &cloned);
	msh_log(state->msh, MSG_DEBUG_EXECUTOR, "Transformed command tokens\n");
	ret = !!err.type;
	if (!err.type)
	{
		backup = node->command.tokens;
		node->command.tokens = cloned;
		msh_dump_tokens(state->msh, cloned);
		msh_log(state->msh, MSG_DEBUG_EXECUTOR, "Preparing command\n");
		ret = msh_exec_command_prepare(state, node);
		node->command.tokens = backup;
	}
	ft_lst_free(&cloned, (t_lst_dealloc) msh_ast_token_free);
	return (ret);
}
