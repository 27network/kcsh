/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_sanitize_check_duplicate.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:56:57 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/14 19:57:03 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#define MSH_SANITIZER_TYPE t_list
#include <msh/ast/sanitizer.h>
#include <msh/log.h>
#include <msh/util.h>

t_ast_error	msh_ast_sanitize_check_duplicate(t_list *current)
{
	static const t_ast_token_type	no_dupes[] = {
		TKN_PIPE, TKN_DELIM, TKN_SEMISEMI};
	t_ast_token						*token;
	t_ast_token						*next;
	size_t							i;

	if (!current->next)
		return (msh_ast_ok());
	token = current->content;
	next = current->next->content;
	if (!token || !next)
		return (msh_ast_errd(AST_ERROR_ALLOC, "sanitize_check_dupes: "
				"empty token", false));
	if (token->type != next->type)
		return (msh_ast_ok());
	i = 0;
	while (i < sizeof(no_dupes) / sizeof(no_dupes[0]))
	{
		if (token->type == no_dupes[i])
			return (msh_ast_errd(AST_ERROR_SYNTAX, (void *)msh_syntax_error(
						token), false));
		i++;
	}
	return (msh_ast_ok());
}
