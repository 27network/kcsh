/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_sanitize_tokens.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:19:01 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/07 19:29:01 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/sanitizer.h>
#include <msh/ast/lexer.h>

t_ast_error	msh_ast_sanitize_tokens(t_list **tokens_ptr,
				t_ast_sanitization_context ctx)
{
	t_list	*tokens;

	if (!tokens_ptr)
		return (msh_ast_errd(AST_ERROR_ALLOC, "invalid token list", false));
	tokens = *tokens_ptr;
	if (!tokens)
		return (msh_ast_ok());
	return (msh_ast_ok());
}
