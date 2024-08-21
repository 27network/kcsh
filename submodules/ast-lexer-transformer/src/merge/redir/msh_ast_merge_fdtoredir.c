/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_merge_fdtoredir.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:35:40 by kiroussa          #+#    #+#             */
/*   Updated: 2024/08/21 17:44:43 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string/parse.h>
#include <msh/ast/transformer.h>

/**
 * Current token list:
 * - TKN_NUMBER(2)
 * - TKN_REDIR[1, >>, ?]
 *
 * Target:
 * - TKN_REDIR(2, >>, ?) 
 *
 * Free strategy:
 * - Current token (no)
 * - Next token (yes)
 * - Next node (yes)
 */
t_ast_token	*msh_ast_merge_fdtoredir(t_list *current, t_ast_token *fd,
			t_ast_token *redir)
{
	long long	number;
	t_list		*next;

	if (!current || !fd || !redir || redir->value.redir.left_fd != -1
		|| ft_strtoll(fd->value.string, &number))
		return (NULL);
	next = current->next;
	if (!next)
		return (NULL);
	redir->value.redir.left_fd = number;
	current->content = redir;
	current->next = next->next;
	ft_lst_delete(next, NULL);
	msh_ast_token_free(fd);
	return (redir);
}
