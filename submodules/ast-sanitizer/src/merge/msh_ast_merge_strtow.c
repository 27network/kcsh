/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_merge_strtow.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:52:00 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/18 00:50:45 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/sanitizer.h>

/**
 * Current token list:
 * - TKN_STRING(...)
 * - TKN_WORD("Hi")
 *
 * Target:
 * - TKN_STRING(... TKN_WORD("Hi"))
 *
 * Free strategy:
 * - Current token (no)
 * - Next token (no)
 * - Next node (yes)
 */
t_ast_token	*msh_ast_merge_strtow(t_list *token, t_ast_token *string,
				t_ast_token *word)
{
	t_list	*next;

	if (!token || !word)
		return (NULL);
	next = token->next;
	if (!next)
		return (NULL);
	if (!ft_lst_tadd(&string->value.list, word))
		return (NULL);
	token->next = next->next;
	ft_lst_delete(next, NULL);
	return (string);
}
