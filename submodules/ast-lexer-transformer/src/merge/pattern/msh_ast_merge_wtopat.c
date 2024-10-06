/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_merge_wtopat.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:05:30 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/07 00:44:05 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <msh/ast/transformer.h>

static t_ast_token	*msh_ast_merge_wtopat_create(
	t_list *token,
	__attribute__((unused))
	t_ast_token *first,
	__attribute__((unused))
	t_ast_token *second,
	t_ast_token *string
) {
	t_list	*next;

	next = token->next;
	if (!next)
		msh_ast_token_free(string);
	if (!next)
		return (NULL);
	msh_ast_token_free(first);
	msh_ast_token_free(second);
	token->next = next->next;
	ft_lst_delete(next, NULL);
	token->content = string;
	return (string);
}

/**
 * Current token list:
 * - TKN_WORD("Hi")
 * - TKN_SUBST("*")
 *
 * Target:
 * - TKN_SUBST("Hi*")
 *
 * Free strategy:
 * - Current token (yes)
 * - Next token (yes)
 * - Next node (yes)
 */
t_ast_token	*msh_ast_merge_wtopat(t_minishell *msh, t_list *token,
				t_ast_token *first, t_ast_token *second)
{
	t_ast_token	*string;
	t_ast_token	*next;

	msh_log(msh, MSG_DEBUG_EXEC_TRANSFORMER, "running merge_wtopat\n");
	if (!token || !first || !second)
		return (NULL);
	string = NULL;
	if (msh_ast_token_new(TKN_SUBST, &string).type || !string)
	{
		if (string)
			msh_ast_token_free(string);
		return (NULL);
	}
	string->value.string = ft_calloc(ft_strlen(first->value.string)
			+ ft_strlen(second->value.string) + 1, sizeof(char));
	if (!string->value.string)
		msh_ast_token_free(string);
	if (!string->value.string)
		return (NULL);
	string->kind = SUBST_PATTERN;
	ft_strcat(string->value.string, first->value.string);
	ft_strcat(string->value.string, second->value.string);
	next = msh_ast_merge_wtopat_create(token, first, second, string);
	msh_log(msh, MSG_DEBUG_EXEC_TRANSFORMER, "merge_wtopat success\n");
	return (next);
}
