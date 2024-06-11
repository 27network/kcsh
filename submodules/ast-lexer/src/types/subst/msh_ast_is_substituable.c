/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_is_substituable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:40:37 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/11 01:25:53 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/ast/lexer.h>
#include <msh/features.h>

static bool	msh_ast_is_subst_name(const char *input, size_t i)
{
	size_t	current;
	char	*buffer;
	bool	ret;

	buffer = ft_calloc(1, i + 1);
	ret = false;
	current = 1;
	while (buffer && current < i)
	{
	}
	return (ret);
}

static bool	msh_ast_is_substituable0(t_ast_lexer *state,
				t_ast_subst_context context)
{
	const bool		in_string = state->delim == '\"';
	const char		next = input[1];
	const size_t	len = ft_strlen(input);
	size_t			i;

	if (next == 0)
		return (false);
	if (next == '(' || next == '{')
		return (true);
	i = 0;
	while (i < len)
	{
		if (msh_ast_is_subst_name(input, i))
			return (true);
		i++;
	}
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
