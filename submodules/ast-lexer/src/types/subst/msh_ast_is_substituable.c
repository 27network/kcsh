/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_is_substituable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:40:37 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/29 22:28:40 by kiroussa         ###   ########.fr       */
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

#define TODO42SH false

static bool	msh_ast_is_substituable_dollar(t_ast_lexer *state, const char *line)
{
	const char	second = line[1];
	const char	third = line[2];

	(void) state;
	if (second == '{' && FEAT_PARSER_PARAM_EXPANSION)
		return (TODO42SH);
	if (second == '(' && third == '(' && FEAT_PARSER_ARITHMETIC)
		return (TODO42SH);
	if (second == '(' && FEAT_PARSER_CONTROL_SUBST)
		return (TODO42SH);
	if (second == '\'' && FEAT_PARSER_ANSI_QUOTING)
		return (TODO42SH);
	if (second == '\"' && FEAT_PARSER_LOCALIZE_QUOTING)
		return (TODO42SH);
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

	if (!state || !state->allow_subst || (state->discrim_mode
			&& state->delim == 0))
		return (false);
	line = &state->input[state->cursor];
	if (!line || !*line)
		return (false);
	ret = false;
	if (*line == '`' && FEAT_PARSER_CONTROL_SUBST)
		ret = true;
	else if (*line == '$')
		ret = msh_ast_is_substituable_dollar(state, line);
	msh_log(state->msh, MSG_DEBUG_TOKENIZER, "is substituable: %s\n",
		msh_strbool(ret));
	return (ret);
}
