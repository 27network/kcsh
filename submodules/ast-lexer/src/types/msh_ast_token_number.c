/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_number.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 02:20:15 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/29 18:50:12 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string/parse.h>
#include <ft/string.h>
#include <limits.h>
#include <msh/ast/lexer.h>
#include <msh/features.h>

#if FEAT_PARSER_42SH_REDIRECTIONS

static bool	msh_is_number(const char *input)
{
	t_str_parseerr	err;
	long long		discard;

	discard = 0;
	err = ft_strtoll(input, &discard);
	if (discard < INT_MIN || discard > INT_MAX)
		return (false);
	return (err == PARSE_SUCCESS);
}

t_ast_error	msh_ast_token_number(t_ast_lexer *state, t_ast_token **tokret,
				size_t *inc)
{
	t_ast_error	err;
	t_ast_token	*tok;
	size_t		i;
	char		*input;

	i = ft_strcspn(state->input + state->cursor, DELIM_CHARS);
	input = ft_strndup(state->input + state->cursor, i);
	if (!input)
		return (msh_ast_errd(AST_ERROR_ALLOC, "msh_ast_token_number", false));
	if (!msh_is_number(input))
	{
		ft_strdel(&input);
		return (msh_ast_errd(AST_ERROR_CANCEL, "not a number", false));
	}
	err = msh_ast_token_new(TKN_NUMBER, &tok);
	if (err.type != AST_ERROR_NONE)
		ft_strdel(&input);
	else
	{
		tok->value.string = input;
		*tokret = tok;
		*inc = i;
	}
	return (err);
}

#else

t_ast_error	msh_ast_token_number(t_ast_lexer *state, t_ast_token **tokret,
				size_t *inc)
{
	(void) state;
	(void) tokret;
	(void) inc;
	return (msh_ast_errd(AST_ERROR_CANCEL, "not implemented", false));
}

#endif // FEAT_PARSER_42SH_REDIRECTIONS
