/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_merge_redirtostring.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:57:52 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/27 16:06:09 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/transformer.h>

/**
 * Current token list:
 * - TKN_REDIR(2, >>, ?)
 * - TKN_STRING(WORD("hello"), SEP(" "), WORD("world"))
 *
 * Target:
 * - TKN_REDIR(2, >>, TKN_STRING(WORD("hello"), SEP(" "), WORD("world")))
 *
 * Free strategy:
 * - Current token (no)
 * - Next token (no)
 * - Next node (yes)
 */
t_ast_token	*msh_ast_merge_redirtostring(t_minishell *msh, t_list *current,
				t_ast_token *redir, t_ast_token *string)
{
	t_list	*next;

	(void)msh;
	msh_log(msh, MSG_DEBUG_EXEC_TRANSFORMER, "merge redirtostring\n");
	if (!current || !redir || !string)
		return (NULL);
	next = current->next;
	if (!next)
		return (NULL);
	redir->value.redir.right_word = string;
	redir->value.redir.state = REDIR_STATE_WORD;
	current->next = next->next;
	ft_lst_delete(next, NULL);
	return (string);
}
