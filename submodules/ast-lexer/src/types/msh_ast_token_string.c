/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_string.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:45:20 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/28 13:31:10 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/lexer.h>

/**
 * @brief Tokenizes a string (double quoted) via a local sublexer
 *
 * If the sublexer fails, fail fast and return the error
 *
 * If the sublexer succeeds, create a new token with the string type
 * and with a token list as a value.
 *
 * NOTE: The sublexer should only be able to tokenize a few types that can
 * actually be found in a string, such as words, separators, substitutions
 */
t_ast_error	msh_ast_token_string(t_ast_lexer *state, t_ast_token **token,
				size_t *inc)
{
	t_ast_lexer	local;
	t_ast_token	*string_tkn;
	t_ast_error	err;

	state->cursor += 1;
	local = msh_ast_lexer_sub(state, "\"");
	err = msh_ast_tokenize(&local);
	if (err.type != AST_ERROR_NONE)
		return (err);
	err = msh_ast_token_new(TKN_STRING, &string_tkn);
	if (err.type != AST_ERROR_NONE)
	{
		if (local.tokens)
			ft_lst_free(&local.tokens,
				(t_lst_dealloc) msh_ast_token_free);
		return (err);
	}
	string_tkn->value.list = local.tokens;
	*token = string_tkn;
	*inc += local.cursor + 1;
	return (err);
}
