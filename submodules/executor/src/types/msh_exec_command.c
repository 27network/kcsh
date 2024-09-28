/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 01:51:37 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/28 20:13:29 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/data/list.h>
#include <msh/ast/transformer.h>
#include <msh/exec.h>
#include <msh/log.h>
#include <stdio.h>
#include <unistd.h>

void	msh_dump_tokens(t_minishell *msh, t_list *tokens);
t_list	*msh_clone_tokens(t_minishell *msh, t_list *tokens);

static int	msh_save_fds(t_minishell *msh, int fds[2])
{
	int		ret;

	(void) msh;
	ret = dup(STDOUT_FILENO);
	if (ret == -1)
		return (0);
	fds[0] = ret;
	ret = dup(STDERR_FILENO);
	if (ret == -1)
	{
		close(fds[0]);
		return (0);
	}
	fds[1] = ret;
	return (1);
}

static int	msh_restore_fds(t_minishell *msh, int fds[2])
{
	int		ret;

	(void) msh;
	ret = dup2(fds[0], STDOUT_FILENO);
	if (ret == -1)
		return (0);
	close(fds[0]);
	ret = dup2(fds[1], STDERR_FILENO);
	if (ret == -1)
		return (0);
	close(fds[1]);
	return (0);
}

static int	msh_exec_command_setup(t_exec_state *state, t_ast_node *node)
{
	pid_t	pid;
	int		save_fds[2];
	int		ret;

	(void) node;
	pid = -1;
	if (state->is_in_pipe) //|| (has_comamnd && is_not_builtin)) 
	{
		pid = msh_fork(state->msh);
		if (pid == -1)
			return (1);
	}
	else
	{
		if (!msh_save_fds(state->msh, save_fds))
			return (1);
	}
	// ret = msh_exec_command_redirections(state, node);
	ret = 1;
	if (state->is_in_pipe)
	{
		if (pid != 0)
			msh_exit(state->msh, 1);
	}
	else if (!msh_restore_fds(state->msh, save_fds))
		return (1);
	return (ret);
}

static int	msh_exec_command_transform(t_exec_state *state, t_ast_node *node)
{
	(void) state;
	(void) node;
	return (msh_exec_command_setup(state, node));
}

__attribute__((unused))
static int	msh_exec_command_prepare(t_exec_state *state, t_ast_node *node)
{
	t_list		*token;
	t_ast_token	*t;
	bool		error;

	token = node->command.tokens;
	error = false;
	while (token && !error)
	{
		t = (t_ast_token *) token->content;
		if (t->type == TKN_REDIR && !ft_lst_tadd(&node->command.redirs, t))
			error = true;
		else if (t->type == TKN_STRING && !ft_lst_tadd(&node->command.args, t))
			error = true;
		else
			printf("unhandled token type %s\n", msh_ast_strtoken(t->type));
		token = token->next;
	}
	if (error)
		msh_error(state->msh, "failed to prepare command (memalloc?)\n");
	else
		error = msh_exec_command_transform(state, node);
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
	ret = !!err.type;
	if (!err.type)
	{
		backup = node->command.tokens;
		node->command.tokens = cloned;
		msh_dump_tokens(state->msh, cloned);
		// ret = msh_exec_command_prepare(state, node);
		node->command.tokens = backup;
	}
	ft_lst_free(&cloned, (t_lst_dealloc) msh_ast_token_free);
	return (ret);
}
