/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_subst_wildcard.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:53:03 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/28 17:06:43 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <msh/ast/lexer.h>
#include <msh/env.h>

#define TKN_ACTUAL TKN_SUBST
#define ALLOC_FAIL "failed to allocate memory for substitution token"

t_ast_error	msh_ast_token_subst_wildcard(t_ast_lexer *state,
				t_ast_token **tknret, size_t *inc)
{
	const char	*input = state->input + state->cursor;
	t_ast_token	*token;
	t_ast_error	err;

	if (!input || *input != '*')
		return (msh_ast_errd(AST_ERROR_UNEXPECTED, "unexpected substitution",
				false));
	err = msh_ast_token_new(TKN_SUBST, &token);
	if (err.type != AST_ERROR_NONE)
		return (err);
	token->kind = SUBST_WILDCARD;
	*tknret = token;
	*inc = 1;
	return (msh_ast_ok());
}
