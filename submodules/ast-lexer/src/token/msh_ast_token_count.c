/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_count.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:56:51 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/04 03:56:59 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/lexer.h>

size_t	msh_ast_token_count(t_list *tokens, t_ast_token_type type)
{
	size_t	count;
	t_list	*node;

	count = 0;
	node = tokens;
	while (node)
	{
		if (((t_ast_token *) node->content)->type == type)
			count++;
		node = node->next;
	}
	return (count);
}
