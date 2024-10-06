/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_merge_pattostr.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:00:01 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/07 00:25:00 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/transformer.h>

/**
 * Current token list:
 * - TKN_SUBST("*")
 * - TKN_STRING(...)
 *
 * Target:
 * - TKN_STRING(TKN_SUBST("*") ...)
 *
 * Free strategy:
 * - Current token (no)
 * - Next token (no)
 * - Next node (yes)
 */
t_ast_token	*msh_ast_merge_pattostr(t_minishell *msh, t_list *token,
				t_ast_token *word, t_ast_token *string)
{
	t_list	*next;

	msh_log(msh, MSG_DEBUG_EXEC_TRANSFORMER, "running merge_pattostr\n");
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
	msh_log(msh, MSG_DEBUG_EXEC_TRANSFORMER, "merge_pattostr success\n");
	return (string);
}
