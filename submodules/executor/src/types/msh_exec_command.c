/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 01:51:37 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/28 18:53:10 by kiroussa         ###   ########.fr       */
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

static int	msh_exec_command_setup(t_exec_state *state, t_ast_node *node)
{
}

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
	if (!error)
		return (msh_exec_command_setup(state, node));
	ft_lst_free(&node->command.redirs, NULL);
	ft_lst_free(&node->command.args, NULL);
	ft_lst_free(&node->command.env, NULL);
	msh_error(state->msh, "failed to prepare command (memalloc?)\n");
	return (1);
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
		ret = msh_exec_command_prepare(state, node);
		node->command.tokens = backup;
	}
	ft_lst_free(&cloned, (t_lst_dealloc) msh_ast_token_free);
	return (ret);
}
