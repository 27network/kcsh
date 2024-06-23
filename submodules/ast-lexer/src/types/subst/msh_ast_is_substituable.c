/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_is_substituable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:40:37 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/23 03:48:02 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/ast/lexer.h>
#include <msh/env.h>
#include <msh/features.h>
#include <stdlib.h>

static bool	msh_ast_is_valid_env_name(const char *name, size_t length)
{
	const char	*buffer = ft_strndup(name, length);
	bool		ret;

	if (!buffer)
		return (false);
	ret = msh_env_is_valid_name(buffer, false);
	free((char *) buffer);
	return (ret);
}

static bool	msh_ast_is_substituable0(t_ast_lexer *state, const char *input)
{
	const bool		in_string = state->delim == '\"';
	const char		next = input[1];
	const size_t	len = ft_strcspn(input, DELIM_CHARS);

	if (next == 0)
		return (false);
	if ((FEAT_PARSER_CONTROL_SUBST && next == '(')
		|| (FEAT_PARSER_PARAM_EXPANSION && next == '{'))
		return (true);
	if (msh_env_is_special_name_starter(next))
		return (true);
	if (msh_ast_is_valid_env_name(input + 1, len))
		return (true);
	if (in_string)
		return (false);
	return ((FEAT_PARSER_ANSI_QUOTING && next == '\'')
		|| (FEAT_PARSER_LOCALIZE_QUOTING && next == '\"'));
}

bool	msh_ast_is_substituable(t_ast_lexer *state)
{
	const char	*line;

	if (!state)
		return (false);
	line = &state->input[state->cursor];
	if (!line || !*line)
		return (false);
	if (*line == '`' && FEAT_PARSER_CONTROL_SUBST)
		return (true);
	if (*line != '$')
		return (false);
	return (msh_ast_is_substituable0(state, line));
}
