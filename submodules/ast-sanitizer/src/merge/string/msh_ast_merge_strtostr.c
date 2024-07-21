/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_merge_strtostr.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:28:23 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/18 00:29:28 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/sanitizer.h>

static t_list	*msh_lst_merge(t_list *first, t_list *second)
{
	t_list	*merged;

	if (!first && !second)
		return (NULL);
	if (!first)
		return (second);
	if (!second)
		return (first);
	merged = ft_lst_last(first);
	merged->next = second;
	return (first);
}

/**
 * Current token list:
 * - TKN_STRING(...)
 * - TKN_STRING(...)
 *
 * Target:
 * - TKN_STRING(... ...)
 *
 * Free strategy:
 * - Current token (no)
 * - Next token (yes)
 * - Next node (yes)
 */
t_ast_token	*msh_ast_merge_strtostr(t_list *token, t_ast_token *first,
				t_ast_token *second)
{
	t_list	*next;

	if (!token || !first || !second)
		return (NULL);
	next = token->next;
	if (!next)
		return (NULL);
	first->value.list = msh_lst_merge(first->value.list, second->value.list);
	second->value.list = NULL;
	token->next = next->next;
	ft_lst_delete(next, (t_lst_dealloc) msh_ast_token_free);
	return (first);
}
