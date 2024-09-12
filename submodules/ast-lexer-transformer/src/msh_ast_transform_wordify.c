/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_transform_wordify.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:56:31 by kiroussa          #+#    #+#             */
/*   Updated: 2024/08/21 17:40:23 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/transformer.h>

static void	msh_ast_transform_try_wordify(t_list *node)
{
	t_ast_token	*token;

	token = node->content;
	if (token && token->type == TKN_NUMBER)
		token->type = TKN_WORD;
}

t_ast_error	msh_ast_transform_wordify(
	[[maybe_unused]] t_minishell *msh,
	t_list **tokens
) {
	t_list		*current;

	if (!tokens || !*tokens)
		return (msh_ast_ok());
	current = *tokens;
	while (current)
	{
		if (current->content)
			msh_ast_transform_try_wordify(current);
		current = current->next;
	}
	return (msh_ast_ok());
}
