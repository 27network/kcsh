/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_node_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:31:21 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/17 18:23:06 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <msh/ast/builder.h>
#include <msh/log.h>

void	msh_dump_tokens(t_minishell *msh, t_list *tokens);

t_ast_error	msh_ast_node_command(t_minishell *msh, t_list *tokens,
				t_ast_node **result)
{
	t_ast_error	error;

	error = msh_ast_node_new(result, NODE_COMMAND);
	if (error.type)
		return (error);
	msh_log(msh, MSG_DEBUG_AST_BUILDER, "building command node\n");
	if (msh->flags.debug_ast)
		msh_dump_tokens(msh, tokens);
	while (tokens && (((t_ast_token *)tokens->content)->type == TKN_SEP))
		tokens = tokens->next;
	if (!tokens)
		return (msh_ast_errd(AST_ERROR_ALLOC, "msh_ast_node_command", true));
	(*result)->command.tokens = tokens;
	return (error);
}
