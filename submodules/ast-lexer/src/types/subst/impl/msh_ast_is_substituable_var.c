/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_is_substituable_var.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:04:21 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/19 18:26:21 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <msh/ast/lexer.h>
#include <msh/env.h>
#include <msh/log.h>
#include <msh/util.h>
#include <stdlib.h>

size_t	msh_ast_get_var_length(char *input, bool is_braces)
{
	size_t	length;
	bool	valid;
	char	c;

	length = 1;
	while (true)
	{
		c = input[length];
		if (c == '\0' || (c == '}' && is_braces))
			return (length);
		input[length] = 0;
		valid = msh_env_is_valid_name(input, false);
		input[length] = c;
		if (!valid)
			return (length - 1);
		length++;
	}
	return (length);
}

bool	msh_ast_is_substituable_var(const char *input)
{
	char	*until_sep;
	size_t	length;
	bool	ret;

	length = msh_ast_get_var_length((char *) input, false);
	if (length <= 0)
		return (false);
	until_sep = ft_strndup(input, length);
	if (!until_sep)
		return (false);
	ret = msh_env_is_valid_name(until_sep, false);
	free(until_sep);
	return (ret);
}
