/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_build_root.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:15:54 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/04 03:16:02 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <msh/ast/builder.h>
#include <msh/log.h>
#include <msh/util.h>

#define NO_TOKENS_MSG "No tokens to define an AST with... what?"

static t_list	*msh_build_backup_list(t_list *tokens);

static t_list	*msh_build_backup_list(t_list *tokens)
{
	t_list		*nodes;
	t_ast_token	*tok;

	nodes = NULL;
	while (tokens)
	{
		if (!ft_lst_tadd(&nodes, tokens))
		{
			ft_lst_free(&nodes, NULL);
			break ;
		}
		tok = (t_ast_token *) tokens->content;
		if (tok->value.list && (tok->type == TKN_GROUP
				|| tok->type == TKN_STRING) && !ft_lst_add(&nodes,
				msh_build_backup_list(tok->value.list)))
		{
			ft_lst_free(&nodes, NULL);
			break ;
		}
		tokens = tokens->next;
	}
	return (nodes);
}

t_ast_error	msh_ast_build_root(t_minishell *msh, t_list *tokens,
					t_ast_node **result)
{
	t_ast_error	err;
	t_list		*token_backup;

	if (!tokens)
		return (msh_ast_errd(AST_ERROR_ALLOC, NO_TOKENS_MSG, false));
	token_backup = msh_build_backup_list(tokens);
	if (!token_backup)
		return (msh_ast_errd(AST_ERROR_ALLOC, "Could not clone tokens", false));
	err = msh_ast_build(msh, tokens, result);
	if (!err.type && *result)
		(*result)->tree_tokens = token_backup;
	else
		ft_lst_free(&token_backup, NULL);
	return (err);
}
