/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_group.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:18:08 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/28 13:55:40 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/lexer.h>
#include <msh/features.h>

static const char	*msh_delim_for(const char c)
{
	if (c == '(')
		return (")");
	if (c == '{' && FEAT_TOK_GROUP)
		return ("}");
	return (0);
}

t_ast_error	msh_ast_token_group(t_ast_lexer *state, t_ast_token **token,
				size_t *inc)
{
	const char	type = state->input[state->cursor];
	t_ast_lexer	local;
	t_ast_token	*group_tkn;
	t_ast_error	err;

	state->cursor += 1;
	local = msh_ast_lexer_sub(state, msh_delim_for(type));
	err = msh_ast_tokenize(&local);
	if (err.type != AST_ERROR_NONE)
		return (err);
	err = msh_ast_token_new(TKN_GROUP, &group_tkn);
	if (err.type != AST_ERROR_NONE)
	{
		ft_lst_free(&local.tokens,
			(t_lst_dealloc) msh_ast_token_free);
		return (err);
	}
	group_tkn->value.list = local.tokens;
	*token = group_tkn;
	*inc += local.cursor + 1;
	return (err);
}
