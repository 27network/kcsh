/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_count.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:56:51 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/08 19:20:40 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/lexer.h>

size_t	msh_ast_token_rcount(t_list *tokens, t_ast_token_type type)
{
	size_t		count;
	t_list		*node;
	t_ast_token	*token;

	count = 0;
	node = tokens;
	while (node)
	{
		token = (t_ast_token *) node->content;
		if (token->type == type)
			count++;
		if (token->type == TKN_GROUP || token->type == TKN_STRING)
			count += msh_ast_token_rcount(token->value.list, type);
		node = node->next;
	}
	return (count);
}

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
