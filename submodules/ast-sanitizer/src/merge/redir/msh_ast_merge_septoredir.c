/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_merge_septoredir.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:34:33 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/21 19:40:51 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/sanitizer.h>

/**
 * Current token list:
 * - TKN_SEP
 * - TKN_REDIR
 *
 * Target:
 * - TKN_REDIR
 *
 * Free strategy:
 * - Current token (yes)
 * - Next token (yes)
 * - Next node (yes)
 */
t_ast_token	*msh_ast_merge_septoredir(t_list *current, t_ast_token *sep,
			t_ast_token *redir)
{
	t_list		*next;

	if (!current || !sep || !redir)
		return (NULL);
	next = current->next;
	if (!next)
		return (NULL);
	current->content = redir;
	current->next = next->next;
	ft_lst_delete(next, NULL);
	msh_ast_token_free(sep);
	return (redir);
}
