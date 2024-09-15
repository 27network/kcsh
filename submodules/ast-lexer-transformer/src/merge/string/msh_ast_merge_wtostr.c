/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_merge_wtostr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:00:01 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/15 23:28:17 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/transformer.h>

/**
 * Current token list:
 * - TKN_WORD("Hi")
 * - TKN_STRING(...)
 *
 * Target:
 * - TKN_STRING(TKN_WORD("Hi") ...)
 *
 * Free strategy:
 * - Current token (no)
 * - Next token (no)
 * - Next node (yes)
 */
t_ast_token	*msh_ast_merge_wtostr(t_list *token, t_ast_token *word,
				t_ast_token *string)
{
	t_list	*next;

	if (!token || !word || !string)
		return (NULL);
	next = token->next;
	if (!next)
		return (NULL);
	if (!ft_lst_tinsert(&string->value.list, word))
		return (NULL);
	token->content = next->content;
	token->next = next->next;
	ft_lst_delete(next, NULL);
	return (string);
}
