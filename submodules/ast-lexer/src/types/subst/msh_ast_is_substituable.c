/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_is_substituable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:40:37 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/16 15:31:37 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <msh/ast/lexer.h>
#include <msh/env.h>
#include <msh/features.h>
#include <msh/log.h>
#include <msh/util.h>
#include <stdlib.h>

bool	msh_ast_is_substituable_var(const char *input);

//TODO: Move this out to a var/ subfolder
bool	msh_ast_is_substituable_var(const char *input)
{
	char	*until_sep;
	size_t	length;
	bool	ret;

	length = ft_strcspn(input, DELIM_CHARS);
	if (!length)
		return (false);
	until_sep = ft_strndup(input, length);
	if (!until_sep)
		return (false);
	ret = msh_env_is_valid_name(until_sep, false);
	free(until_sep);
	return (ret);
}

static bool	msh_ast_is_substituable_dollar(t_ast_lexer *state, const char *line)
{
	const char	first = line[0];
	const char	second = line[1];
	const char	third = line[2];

	(void) state;
	if (first != '$')
		return (false);
	if (second == '{' && FEAT_PARSER_PARAM_EXPANSION)
		return (false); //TODO(42sh)
	if (second == '(' && third == '(' && FEAT_PARSER_ARITHMETIC)
		return (false); //TODO(42sh)
	if (second == '(' && FEAT_PARSER_CONTROL_SUBST)
		return (false); //TODO(42sh)
	if (second == '\'' && FEAT_PARSER_ANSI_QUOTING)
		return (false); //TODO(42sh)
	if (second == '\"' && FEAT_PARSER_LOCALIZE_QUOTING)
		return (false); //TODO(42sh)
	if (msh_env_is_special_name_starter(second))
		return (true);
	return (msh_ast_is_substituable_var(line + 1));
}

/*
 * Different types:
 * - $something
 * - ${}
 * - $()
 * - $(())
 * - ``
 * - $'' or $""
 */
bool	msh_ast_is_substituable(t_ast_lexer *state)
{
	const char	*line;
	bool		ret;

	if (!state)
		return (false);
	line = &state->input[state->cursor];
	if (!line || !*line)
		return (false);
	ret = false;
	if (*line == '`' && FEAT_PARSER_CONTROL_SUBST)
		ret = true;
	else if (*line == '$')
		ret = msh_ast_is_substituable_dollar(state, line);
	msh_log(state->msh, MSG_DEBUG_AST_TOKENIZER, "is substituable: %s\n",
		msh_strbool(ret));
	return (ret);
}
