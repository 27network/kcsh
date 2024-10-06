/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_merge_strtopat.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:52:00 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/07 00:44:13 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/transformer.h>

/**
 * Current token list:
 * - TKN_STRING(...)
 * - TKN_SUBST("*")
 *
 * Target:
 * - TKN_STRING(... TKN_SUBST("*"))
 *
 * Free strategy:
 * - Current token (no)
 * - Next token (no)
 * - Next node (yes)
 */
t_ast_token	*msh_ast_merge_strtopat(t_minishell *msh, t_list *token,
				t_ast_token *string, t_ast_token *word)
{
	t_list	*next;

	msh_log(msh, MSG_DEBUG_EXEC_TRANSFORMER, "running merge_strtopat\n");
	if (!token || !word)
		return (NULL);
	next = token->next;
	if (!next)
		return (NULL);
	if (!ft_lst_tadd(&string->value.list, word))
		return (NULL);
	token->next = next->next;
	ft_lst_delete(next, NULL);
	msh_log(msh, MSG_DEBUG_EXEC_TRANSFORMER, "merge_strtopat success\n");
	return (string);
}
