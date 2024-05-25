/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_tokenize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:45:27 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/25 09:36:09 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/lexer.h>
#define LEXER_INPUT_ALLOC_ERR ": failed to allocate memory for command input"
#define TOKEN_NODE_ALLOC_ERR ": failed to allocate memory for token node"

static t_ast_error	msh_ast_next_token(t_ast_lexer *state, t_token **token,
						size_t *inc)
{
	const char	*input = &state->input[state->cursor];
	t_ast_error	err;

	err = msh_ast_ok();
	if (*input == '\n')
		err = msh_ast_token_simple(TKN_NEWLINE, token, inc, 1);
	return (err);
}

t_ast_error	msh_ast_tokenize(t_ast_lexer *state)
{
	t_ast_error	err;
	t_ast_token	*token;
	size_t		inc;

	if (!state->input)
		return (msh_ast_err(AST_ERROR_ALLOC, LEXER_INPUT_ALLOC_ERR, false));
	err = msh_ast_ok();
	while (err.type == AST_ERROR_NONE && state->input[state->cursor])
	{
		err = msh_ast_next_token(state, &token, &inc);
		if (err.type != AST_ERROR_NONE)
			break ;
		if (!ft_lst_tadd(&state->tokens, token))
		{
			err = msh_ast_err(AST_ERROR_ALLOC, TOKEN_NODE_ALLOC_ERR, false);
			if (token)
				free(token);
			token = NULL;
			break ;
		}
		token = NULL;
		state->cursor += inc;
	}
	return (err);
}
