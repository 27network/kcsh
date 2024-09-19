/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_sanitize_token_dropseps.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:25:09 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/19 05:15:12 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/sanitizer.h>
#include <msh/log.h>
#include <msh/util.h>

t_ast_error	msh_ast_sanitize_token_duplicate(t_minishell *msh, t_list *current);

t_ast_error	msh_ast_sanitize_token_dropseps(t_minishell *msh,
						t_list *current, t_ast_token *prev_tkn)
{
	t_ast_token	*tkn;
	t_ast_token	*next_tkn;
	t_list		fake_first;
	t_list		fake_last;

	if (!current || !current->content || !prev_tkn || !current->next)
		return (msh_ast_ok());
	tkn = (t_ast_token *) current->content;
	if (tkn->type != TKN_SEP)
		return (msh_ast_ok());
	next_tkn = (t_ast_token *) current->next->content;
	fake_first.content = prev_tkn;
	fake_first.next = &fake_last;
	fake_last.content = next_tkn;
	fake_last.next = NULL;
	return (msh_ast_sanitize_token_duplicate(msh, &fake_first));
}
