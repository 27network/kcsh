/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_word.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 02:44:38 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/27 06:43:24 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <ft/string.h>
#include <msh/ast/lexer.h>
#include <stdlib.h>

#include <stdio.h>

#define WORD_END "unexpected end of word"
#define WORD_ALLOC_FAIL ": failed to allocate word"

t_ast_error	msh_ast_token_word(t_ast_lexer *s, t_ast_token **tokret,
				size_t *inc)
{
	const bool	escaping = (s->input[s->cursor] == '\\'
			&& s->allow_escape);
	t_ast_token	*token;
	t_ast_error	err;
	size_t		size;

	size = 1;
	s->cursor += escaping;
	if (!escaping)
		size = ft_max(0, ft_strcspn(s->input + s->cursor, DELIM_CHARS));
	if (escaping && s->input[s->cursor] == '\n' && s->input[s->cursor + 1] == 0)
		return (msh_ast_errd(AST_ERROR_UNEXPECTED, "newline escape", true));
	if (size == 0)
		return (msh_ast_errd(AST_ERROR_UNEXPECTED, WORD_END, true));
	err = msh_ast_token_new(TKN_WORD, &token);
	if (err.type != AST_ERROR_NONE)
		return (err);
	token->value.string = ft_strndup(s->input + s->cursor, size);
	if (!token->value.string)
		free(token);
	if (!token->value.string)
		return (msh_ast_errd(AST_ERROR_ALLOC, WORD_ALLOC_FAIL, false));
	*tokret = token;
	*inc = size;
	return (err);
}
