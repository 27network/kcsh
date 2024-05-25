/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_string.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:45:20 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/25 10:46:07 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/lexer.h>

// tokenize the inside of the string via the local sublexer
// if the sublexer fails, fail fast and return the error
// if the sublexer succeeds, create a new token with the string type
// and with a token list as a value.
t_ast_error	msh_ast_token_string(t_ast_lexer *state, t_ast_token **token,
				size_t *inc)
{
	const char			quote_type = state->input[state->cursor];
	const t_ast_lexer	local = msh_ast_lexer_sub(state, quote_type);
	t_ast_token			*string_tkn;
	t_ast_error			err;

	err = msh_ast_tokenize(&local);
	if (err.type != AST_ERROR_NONE)
		return (err);
	err = msh_ast_token_new(TKN_STRING, &string_tkn);
	if (err.type != AST_ERROR_NONE)
	{
		if (local.tokens)
			ft_lst_tclear(&local.tokens, free);
		return (err);
	}
	string_tkn->list = local.tokens;
	return (err);
}
