/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_word_into_subst.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 22:59:39 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/09 02:45:39 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/ast/lexer.h>
#include <msh/features.h>
#include <stdlib.h>

#define ALLOWED "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_/ \n\
\t|&<>)};"

static t_ast_error	msh_ast_token_word_into_subst_tilde(t_ast_lexer *state,
						t_ast_token **tokret, t_ast_error err, size_t *inc)
{
	const char	*input = state->input + state->cursor + *inc;
	t_ast_token	*token;
	size_t		i;

	token = *tokret;
	if (token->value.string[0] == '~')
	{
		i = ft_strlen(token->value.string);
		if ((token->value.string[1] == 0 || token->value.string[i - 1]
				!= '/') && input[0] != 0 && !ft_strchr(ALLOWED, input[0]))
			return (err);
		token->type = TKN_SUBST;
		token->kind = SUBST_TILDE;
	}
	return (err);
}

static t_ast_error	msh_ast_token_word_into_subst_glob(t_ast_lexer *state,
						t_ast_token **tokret, t_ast_error err, size_t *inc)
{
	t_ast_token	*token;
	size_t		len;

	(void)state;
	(void)inc;
	token = *tokret;
	len = ft_strlen(token->value.string);
	if (len == 1 && (token->value.string[0] == '*'
			|| (token->value.string[0] == '?' && FEAT_PATTERN_MATCHING_FULL)))
	{
		token->type = TKN_SUBST;
		token->kind = SUBST_PATTERN;
	}
	return (err);
}

t_ast_error	msh_ast_token_word_into_subst(t_ast_lexer *state,
						t_ast_token **tokret, t_ast_error err, size_t *inc)
{
	t_ast_token	*token;

	token = *tokret;
	if (!token || !token->value.string)
		return (err);
	if (state->delim && ft_strcmp(state->delim, "\"") == 0)
		return (err);
	if (!err.type && token->type == TKN_WORD && FEAT_TILDE_EXPANSION)
		err = msh_ast_token_word_into_subst_tilde(state, tokret, err, inc);
	if (!err.type && token->type == TKN_WORD && FEAT_PATTERN_MATCHING_GLOB)
		err = msh_ast_token_word_into_subst_glob(state, tokret, err, inc);
	return (err);
}
