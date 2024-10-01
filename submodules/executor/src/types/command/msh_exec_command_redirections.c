/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_command_redirections.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:51:19 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/01 18:07:49 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <msh/ast/builder.h>
#include <msh/ast/transformer.h>
#include <msh/exec.h>
#include <msh/log.h>
#include <msh/signal.h> 
#include <msh/util.h>
#include <string.h>
#include <unistd.h>

#define LEVEL MSG_DEBUG_EXECUTOR

int		msh_exec_simple(t_exec_state *state, char **args);

int		msh_exec_command_redirect_file_in(t_exec_state *state,
			t_ast_token *token);
int		msh_exec_command_redirect_file_out(t_exec_state *state,
			t_ast_token *token);

#define TODO_42SH 1

static int	msh_exec_command_setup_redir(t_exec_state *state,
				t_ast_token *token)
{
	if (token->kind == REDIR_HERESTRING)
		return (TODO_42SH);
	if (token->kind == REDIR_HEREDOC_STRIP || token->kind == REDIR_HEREDOC)
		return (msh_exec_command_redirect_file_in(state, token));
	if (token->kind == REDIR_FILE_CLOBBER_A
		|| token->kind == REDIR_FILE_CLOBBER)
		return (TODO_42SH);
	if (token->kind == REDIR_FILE_APPEND)
		return (msh_exec_command_redirect_file_out(state, token));
	if (token->kind == REDIR_FILE_INOUT)
		return (msh_exec_command_redirect_file_in(state, token));
	if (token->kind == REDIR_FD_IN)
		return (TODO_42SH);
	if (token->kind == REDIR_FD_OUT)
		return (TODO_42SH);
	if (token->kind == REDIR_FILE_OUT_A)
		return (msh_exec_command_redirect_file_out(state, token));
	if (token->kind == REDIR_FILE_IN)
		return (msh_exec_command_redirect_file_in(state, token));
	if (token->kind == REDIR_FILE_OUT)
		return (msh_exec_command_redirect_file_out(state, token));
	return (1);
}

static int	msh_exec_command_setup_redirs(t_exec_state *state,
				t_ast_node *node)
{
	t_list		*token;
	t_ast_token	*tkn;
	int			ret;

	token = node->command.redirs;
	ret = 0;
	while (token && !ret)
	{
		tkn = (t_ast_token *) token->content;
		ret = msh_exec_command_setup_redir(state, tkn);
		token = token->next;
	}
	return (ret);
}

static int	msh_exec_command_execute_final(t_exec_state *state,
				t_ast_node *node)
{
	char	**args;
	size_t	i;
	t_list	*token;
	int		ret;

	args = ft_calloc(ft_lst_size(node->command.args) + 1, sizeof(char *));
	if (!args)
		msh_error(state->msh, "failed to allocate args\n");
	if (!args)
		return (1);
	token = node->command.args;
	i = 0;
	while (token)
	{
		args[i++] = ((t_ast_token *) token->content)->value.string;
		token = token->next;
	}
	ret = msh_exec_simple(state, args);
	msh_signal_init(state->msh, false);
	free(args);
	return (ret);
}

int	msh_exec_command_redirections(t_exec_state *state,
				t_ast_node *node)
{
	int		ret;

	ret = msh_exec_command_setup_redirs(state, node);
	if (ret != 0)
	{
		state->msh->execution_context.exit_code = ret;
		return (ret);
	}
	if (ft_lst_size(node->command.args) != 0)
		ret = msh_exec_command_execute_final(state, node);
	return (ret);
}
