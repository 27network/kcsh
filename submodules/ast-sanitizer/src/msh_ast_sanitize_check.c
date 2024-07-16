/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_sanitize_check.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:04:58 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/16 18:24:30 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/sanitizer.h>

static t_ast_error	msh_ast_sanitize_check_duplicate(t_list *current)
{
	static const t_ast_token_type	no_dupes[] = {
		TKN_PIPE, TKN_AMP, TNK_DELIM, TKN_SEMISEMI
	};
	t_ast_token						*token;
	t_ast_token						*next;
	size_t							i;

	if (!current->next)
		return (msh_ast_ok());
	token = current->content;
	next = current->next->content;
	if (!token || !next)
		return (msh_ast_errd(AST_ERROR_ALLOC, "empty token", false));
	if (token->type != next->type)
		return (msh_ast_ok());
	i = 0;
	while (i < sizeof(no_dupes) / sizeof(no_dupes[0]))
	{
		if (token->type == no_dupes[i])
			return (msh_ast_errd(AST_ERROR_SYNTAX, ..., false));
		i++;
	}
	return (msh_ast_ok());
}

t_ast_error	msh_ast_sanitize_check(t_list **tokens)
{
	t_list		*last;
	t_list		*current;
	t_ast_error	err;

	last = NULL;
	current = *tokens;
	err = msh_ast_ok();
	while (current && err.type == AST_ERROR_NONE)
	{
		err = msh_ast_sanitize_check_duplicate(current);
		if (err.type != AST_ERROR_NONE)
			break ;
		if (last && last->content)
			err = msh_ast_sanitize_check_order(last->content, current->content);
		last = current;
		current = current->next;
	}
	return (err);
}
