/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_word.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 02:44:38 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/29 22:30:56 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <ft/string.h>
#include <msh/ast/lexer.h>
#include <msh/features.h>
#include <msh/log.h>
#include <stdlib.h>

#define TKN_ACTUAL TKN_WORD
#define WORD_END "unexpected end of word"
#define WORD_ALLOC_FAIL ": failed to allocate word"
#define ALLOWED_STRING_ESCAPES "$`\"\\\n"
#define ALLOWED "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_/ \n\t"

static t_ast_error	msh_transform_into_subst(t_ast_lexer *state,
						t_ast_token **tokret, t_ast_error err, size_t *inc)
{
	const char	*input = state->input + state->cursor + *inc;
	t_ast_token	*token;
	size_t		i;

	token = *tokret;
	if (token && token->value.string && FEAT_TILDE_EXPANSION)
	{
		if (token->value.string[0] == '~')
		{
			i = ft_strlen(token->value.string);
			if ((token->value.string[1] == 0 || token->value.string[i - 1]
					!= '/') && input[0] != 0 && !ft_strchr(ALLOWED, input[0]))
				return (err);
			token->type = TKN_SUBST;
			token->kind = SUBST_TILDE;
		}
	}
	return (err);
}

static t_ast_error	msh_ast_make_word(t_ast_lexer *state, t_ast_token **tokret,
						size_t *inc, const char *word)
{
	char		*value;
	t_ast_error	err;

	if (!word)
		TRACE(state, TKN_ACTUAL, 2);
	if (!word)
		return (msh_ast_errd(AST_ERROR_ALLOC, WORD_ALLOC_FAIL, false));
	msh_log(state->msh, MSG_DEBUG_TOKENIZER, "making word %s\n", word);
	value = ft_strdup(word);
	if (!value)
		TRACE(state, TKN_ACTUAL, 2);
	if (!value)
		return (msh_ast_errd(AST_ERROR_ALLOC, WORD_ALLOC_FAIL, false));
	err = msh_ast_token_new(TKN_WORD, tokret);
	if (err.type != AST_ERROR_NONE)
	{
		TRACE(state, TKN_ACTUAL, 2);
		free(value);
		return (err);
	}
	(*tokret)->value.string = value;
	*inc += ft_strlen(word);
	TRACE(state, TKN_ACTUAL, (err.type != AST_ERROR_NONE) * 2);
	return (msh_transform_into_subst(state, tokret, err, inc));
}

/**
 * Escaped words exist in three fashion:
 * - Escaped regular characters
 * - "Escaped" null character
 * - Escaped newlines
 *
 * For characters, nothing special is done, a word token is created with the
 * unique char as a string value.
 *
 * For null characters, meaning if the escape is at the end of the input,
 * don't escape. `bash -c 'echo test \' just appends the backslash as an
 * individual word.
 *
 * For newlines, it depends on the context:
 * - If the newline is the last character of the input, the backslash is
 *   considered "escaping the input end", and returns a retry-able error to
 *   continue prompting. This allows for deliberate multi-line input.
 * - If the newline is in the middle of the input, its considered as if it
 *   previously was an "escaped input end", and thus is ignored. We make an
 *   empty word token to signify this and ignore the newline.
 *
 * See: https://www.gnu.org/software/bash/manual/html_node/Escape-Character.html
 */
static t_ast_error	msh_escaped_word(t_ast_lexer *state, t_ast_token **tokret,
						size_t *inc)
{
	char		target;
	char		*word;
	t_ast_error	err;

	target = state->input[state->cursor + 1];
	if (target == 0)
		return (msh_ast_make_word(state, tokret, inc, "\\"));
	if (target == '\n' && state->input[state->cursor + 2] == 0)
	{
		TRACE(state, TKN_ACTUAL, 2);
		return (msh_ast_errd(AST_ERROR_WARNING, "newline escape", true));
	}
	if (target == '\n')
	{
		*inc = 2;
		return (msh_ast_make_word(state, tokret, inc, ""));
	}
	word = ft_ctostr(target);
	err = msh_ast_make_word(state, tokret, inc, word);
	if (word)
		free(word);
	*inc += 1;
	return (err);
}

static bool	msh_should_escape(t_ast_lexer *state)
{
	const bool	escaping = (state->input[state->cursor] == '\\');
	const bool	inside_string = msh_ast_lexer_is_delim(state, '\"');

	if (!escaping)
		return (false);
	if (!state->allow_escape)
		return (false);
	if (!inside_string)
		return (true);
	return (ft_strchr(ALLOWED_STRING_ESCAPES, state->input[state->cursor + 1]));
}

t_ast_error	msh_ast_token_word(t_ast_lexer *state, t_ast_token **tokret,
				size_t *inc)
{
	t_ast_error	err;
	size_t		size;
	char		*value;

	TRACE(state, TKN_ACTUAL, 1);
	if (FEAT_PARSER_INHIBITORS && msh_should_escape(state))
		return (msh_escaped_word(state, tokret, inc));
	if (state->allow_subst)
		size = ft_strcspn(state->input + state->cursor, DELIM_CHARS);
	else
		size = ft_strcspn(state->input + state->cursor, DELIM_CHARS_HEREDOC);
	if (size == 0 && state->input[state->cursor] != '\0')
		size++;
	value = ft_strndup(state->input + state->cursor, size);
	err = msh_ast_make_word(state, tokret, inc, value);
	if (value)
		free(value);
	return (err);
}
