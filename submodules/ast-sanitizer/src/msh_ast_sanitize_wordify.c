/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_sanitize_wordify.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:56:31 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/21 16:50:01 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/sanitizer.h>

static void	msh_ast_sanitize_try_wordify(t_list *node)
{
	t_ast_token	*token;

	token = node->content;
	if (token && token->type == TKN_NUMBER)
		token->type = TKN_WORD;
}

t_ast_error	msh_ast_sanitize_wordify(
	__attribute__((unused)) t_minishell *msh,
	t_list **tokens
) {
	t_list		*current;

	if (!tokens || !*tokens)
		return (msh_ast_ok());
	current = *tokens;
	while (current)
	{
		if (current->content)
			msh_ast_sanitize_try_wordify(current);
		current = current->next;
	}
	return (msh_ast_ok());
}
