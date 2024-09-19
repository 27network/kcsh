/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_sanitize_token_duplicate.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:56:57 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/19 07:34:46 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#define MSH_SANITIZER_TYPE t_list
#include <msh/ast/sanitizer.h>
#include <msh/log.h>
#include <msh/util.h>

const char	*msh_ast_strtoken_simple_impl(t_ast_token *token,
				const char *paran);

t_ast_error	msh_ast_sanitize_token_duplicate(t_minishell *msh, t_list *current)
{
	static const t_ast_token_type	no_dupes[] = {
		TKN_PIPE, TKN_DELIM, TKN_SEMISEMI, TKN_GROUP};
	t_ast_token						*token;
	t_ast_token						*next;
	size_t							i;

	msh_log(msh, MSG_DEBUG_TOKEN_SANITIZER, "sanitize_check_duplicate\n");
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
			return (msh_ast_errd(AST_ERROR_SYNTAX,
					(void *)msh_syntax_error_impl(token, "("), false));
		i++;
	}
	return (msh_ast_ok());
}
