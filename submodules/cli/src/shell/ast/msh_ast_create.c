/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 22:35:02 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/13 15:27:04 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/builder.h>
#include <msh/ast/sanitizer.h>

/**
 * Removes the last \n from the token list, since it's from our linelib
 */
static int	msh_strip_last_delim(t_list *tokens)
{
	t_list	*node;

	if (!tokens || !tokens->content)
		return (1);
	if (((t_ast_token *) tokens->content)->type == TKN_DELIM && !tokens->next)
		return (2);
	node = tokens;
	while (node && node->next && node->next->next)
		node = node->next;
	if (node->next && !node->next->next && ((t_ast_token *) node->next->content)
		->type == TKN_DELIM && ((t_ast_token *) node->next->content)->kind
		== DELIM_NEWLINE)
	{
		ft_lst_delete(node->next, (t_lst_dealloc) msh_ast_token_free);
		node->next = NULL;
	}
	return (0);
}

int	msh_ast_create(t_minishell *msh, t_list *tokens, t_ast_node **result)
{
	t_ast_error	err;
	int			ret;

	*result = NULL;
	ret = msh_strip_last_delim(tokens);
	if (ret)
		return (ret - 1);
	err = msh_ast_build(msh, tokens, result);
	if (err.type != AST_ERROR_NONE)
	{
		msh_ast_error_print(msh, err);
		*result = NULL;
	}
	else
	{
		err = msh_ast_sanitize(msh, result);
		if (err.type != AST_ERROR_NONE)
			msh_ast_error_print(msh, err);
		if (err.type != AST_ERROR_NONE)
			*result = NULL;
	}
	return (*result != NULL);
}
