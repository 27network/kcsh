/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_merge_redirtosep.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:43:02 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/27 15:31:50 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/sanitizer.h>

/**
 * Current token list:
 * - TKN_REDIR
 * - TKN_SEP
 *
 * Target:
 * - TKN_REDIR
 *
 * Free strategy:
 * - Current token (no)
 * - Next token (yes)
 * - Next node (yes)
 */
t_ast_token	*msh_ast_merge_redirtosep(t_list *current,
				t_ast_token *redir, t_ast_token *sep)
{
	t_list		*next;

	if (!current || !sep || !redir)
		return (NULL);
	next = current->next;
	if (!next)
		return (NULL);
	current->next = next->next;
	ft_lst_delete(next, NULL);
	msh_ast_token_free(sep);
	return (redir);
}
