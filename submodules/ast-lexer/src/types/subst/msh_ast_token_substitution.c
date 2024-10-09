/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_substitution.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 03:44:51 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/09 02:37:53 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/ast/lexer.h>
#include <msh/features.h>

#define TKN_ACTUAL TKN_SUBST

t_ast_error	msh_ast_token_subst_var(t_ast_lexer *state, t_ast_token **tknret,
				size_t *inc);

static t_ast_error	msh_ast_token_substitution_underlying(
	const char *input,
	t_ast_lexer *state,
	t_ast_token **tokret,
	size_t *inc
) {
	const char	first = input[0];
	const char	second = input[1];
	const char	third = input[2];

	if (first == '`' && FEAT_PARSER_CONTROL_SUBST)
		return (msh_ast_errd(AST_ERROR_UNEXPECTED, "` not impl", false));
	if (first == '$')
	{
		if (second == '{' && FEAT_PARSER_PARAM_EXPANSION)
			return (msh_ast_errd(AST_ERROR_UNEXPECTED, "${} not impl", false));
		if (second == '(' && third == '(' && FEAT_PARSER_ARITHMETIC)
			return (msh_ast_errd(AST_ERROR_UNEXPECTED, "$(( not impl", false));
		if (second == '(' && FEAT_PARSER_CONTROL_SUBST)
			return (msh_ast_errd(AST_ERROR_UNEXPECTED, "$() not impl", false));
		return (msh_ast_token_subst_var(state, tokret, inc));
	}
	return (msh_ast_errd(AST_ERROR_UNEXPECTED, "unexpected substitution", 0));
}

t_ast_error	msh_ast_token_substitution(t_ast_lexer *state, t_ast_token **tokret,
				size_t *inc)
{
	const char	*input = state->input + state->cursor;
	t_ast_error	err;

	if (!input || !*input)
		return (msh_ast_errd(AST_ERROR_UNEXPECTED, "unexpected substitution",
				false));
	TRACE(state, TKN_ACTUAL, 1);
	err = msh_ast_token_substitution_underlying(input, state, tokret, inc);
	if (err.type != AST_ERROR_NONE)
		TRACE(state, TKN_ACTUAL, 2);
	else
		TRACE(state, TKN_ACTUAL, 0);
	return (err);
}
