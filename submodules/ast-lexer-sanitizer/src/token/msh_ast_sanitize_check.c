/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_sanitize_check.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 06:39:12 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/04 06:39:22 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#define MSH_SANITIZER_TYPE t_list
#include <msh/ast/sanitizer.h>
#include <msh/log.h>
#include <msh/util.h>

t_ast_error	msh_ast_sanitize_token_dropseps(t_minishell *msh,
				t_list *current, t_ast_token *prev_tkn);
t_ast_error	msh_ast_sanitize_token_duplicate(t_minishell *msh, t_list *current);
t_ast_error	msh_ast_sanitize_token_first(t_minishell *msh, t_list *current,
				t_ast_token *token);
t_ast_error	msh_ast_sanitize_token_recurse(t_minishell *msh, t_list *current,
				t_ast_token *token);
t_ast_error	msh_ast_sanitize_token_word_before(t_minishell *msh,
				t_list *current, t_ast_token *prev_tkn);

t_ast_error	msh_ast_sanitize_check(
	t_minishell *msh,
	t_list *current,
	t_ast_token *prev,
	t_ast_token *curr
) {
	t_ast_error	err;

	msh_log(msh, MSG_DEBUG_TOKEN_SANITIZER, "sanitize_check: ");
	if (msh->flags.debug_token_sanitizer)
		msh_ast_token_print(msh, curr);
	if (!prev)
		err = msh_ast_sanitize_token_first(msh, current, curr);
	if (err.type == AST_ERROR_NONE)
		err = msh_ast_sanitize_token_duplicate(msh, current);
	if (prev && err.type == AST_ERROR_NONE)
	{
		err = msh_ast_sanitize_token_word_before(msh, current, prev);
		if (err.type == AST_ERROR_NONE)
			err = msh_ast_sanitize_token_dropseps(msh, current, prev);
	}
	if (err.type == AST_ERROR_NONE)
		err = msh_ast_sanitize_token_recurse(msh, current, curr);
	return (err);
}
