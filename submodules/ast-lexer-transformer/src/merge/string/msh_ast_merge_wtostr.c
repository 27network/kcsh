/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_merge_wtostr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:00:01 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/17 17:18:24 by kiroussa         ###   ########.fr       */
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
t_ast_token	*msh_ast_merge_wtostr(t_minishell *msh, t_list *token,
				t_ast_token *word, t_ast_token *string)
{
	t_list	*next;

	msh_log(msh, MSG_DEBUG_EXEC_TRANSFORMER, "running merge_wtostr\n");
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
	msh_log(msh, MSG_DEBUG_EXEC_TRANSFORMER, "merge_wtostr success\n");
	return (string);
}
