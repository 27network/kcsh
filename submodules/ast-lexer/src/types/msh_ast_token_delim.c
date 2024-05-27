/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_delim.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 02:22:53 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/27 02:44:19 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/ast/lexer.h>

static t_ast_error	msh_delim_find_kind(const char *input,
						t_ast_delim_type *type)
{
	if (!ft_strncmp(input, "&&", 2))
		*type = DELIM_AND;
	else if (!ft_strncmp(input, "||", 2))
		*type = DELIM_OR;
	else if (*input == ';')
		*type = DELIM_SEMICOLON;
	else if (*input == '\n')
		*type = DELIM_NEWLINE;
	else
		return (msh_ast_errd(AST_ERROR_UNEXPECTED, "unexpected delimiter",
				false));
	return (msh_ast_ok());
}

t_ast_error	msh_ast_token_delim(t_ast_lexer *state, t_ast_token **tokret,
				size_t *inc)
{
	t_ast_token			*token;
	t_ast_delim_type	kind;
	t_ast_error			err;

	err = msh_delim_find_kind(state->input + state->cursor, &kind);
	if (err.type != AST_ERROR_NONE)
		return (err);
	err = msh_ast_token_new(TKN_DELIM, &token);
	if (err.type != AST_ERROR_NONE)
		return (err);
	token->kind = kind;
	token->value.data = NULL;
	*tokret = token;
	*inc += 1 + (kind == DELIM_AND || kind == DELIM_OR);
	return (err);
}
