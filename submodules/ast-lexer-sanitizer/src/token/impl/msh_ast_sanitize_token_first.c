/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_sanitize_token_first.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:12:37 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/15 16:49:07 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#define MSH_SANITIZER_TYPE t_list
#include <msh/ast/sanitizer.h>
#include <msh/log.h>
#include <msh/util.h>

const char	*msh_syntax_error(t_ast_token *token);

t_ast_error	msh_ast_sanitize_token_first(
	t_minishell *msh,
	t_list *current,
	t_ast_token *token
) {
	if (!current || !token)
		return (msh_ast_ok());
	msh_log(msh, MSG_DEBUG_TOKEN_SANITIZER, "sanitize_check_first: ");
	if (msh->flags.debug_token_sanitizer)
		msh_ast_token_print(msh, token);
	if (token->type == TKN_PIPE || token->type == TKN_DELIM
		|| token->type == TKN_SEMISEMI)
		return (msh_ast_errd(AST_ERROR_SYNTAX, (void *)msh_syntax_error(
					token), false));
	return (msh_ast_ok());
}
