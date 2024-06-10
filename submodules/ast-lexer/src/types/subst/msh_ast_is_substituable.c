/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_is_substituable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:40:37 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/07 19:45:22 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/ast/lexer.h>
#include <msh/features.h>

static bool	msh_is_variable_starter(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (true);
	if (c == '?')
		return (true);
	if (FEAT_PARSER_PARAM_EXPANSION)
	{
		if (c == '#' || c == '$' || c == '!' || c == '@')
			return (true);
	}
	return (false);
}

static bool	msh_ast_is_substituable0(t_ast_lexer *state,
				t_ast_subst_context context)
{
	const bool	in_string = state->delim == '\"';
	const char	next = input[1];

	if (next == 0)
		return (false);
	if (next == '(' || next == '{')
		return (true);
	if (in_string)
		return (false);
	return (next == '\'' || next == '\"');
}

bool	msh_ast_is_substituable(t_ast_lexer *state, t_ast_subst_context context)
{
	const char	*line;

	if (!state)
		return (false);
	line = &state->input[state->cursor];
	if (!line || !*line)
		return (false);
	return (msh_ast_is_substituable0(state, context));
}
