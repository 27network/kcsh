/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_sanitize_token_recurse.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 15:13:08 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/04 06:42:11 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#define MSH_SANITIZER_TYPE t_list
#include <msh/ast/sanitizer.h>
#include <msh/log.h>
#include <msh/util.h>

const char	*msh_syntax_error(t_ast_token *token);

t_ast_error	msh_ast_sanitize_token_recurse(
	t_minishell *msh,
	t_list *current,
	t_ast_token *token
) {
	t_ast_error	err;

	if (!current || !token)
		return (msh_ast_ok());
	err = msh_ast_ok();
	msh_log(msh, MSG_DEBUG_TOKEN_SANITIZER, "sanitize_token_recurse: ");
	if (msh->flags.debug_token_sanitizer)
		msh_ast_token_print(msh, token);
	if (token->type == TKN_GROUP)
	{
		if (!token->value.list)
			return (msh_ast_errd(AST_ERROR_SYNTAX, (void *)
					msh_syntax_error(token), false));
		err = msh_ast_sanitize_tokens(msh, &token->value.list);
		if (err.type == AST_ERROR_CANCEL)
			return (msh_ast_errd(AST_ERROR_SYNTAX, (void *)
					msh_syntax_error(token), false));
	}
	return (err);
}
