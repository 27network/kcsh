/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_tokenize_variable.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:54:42 by kiroussa          #+#    #+#             */
/*   Updated: 2024/02/29 20:03:37 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#define TOKENIZER_TYPES
#include <msh/ast/tokenizer.h>

t_token	*msh_ast_tokenize_variable(const char *line, size_t *cursor)
{
	size_t	start;
	size_t	end;
	char	*str;

	start = *cursor;
	end = start + 1;
	while (line[end] && ft_strchr(_LOWERCASE _UPPERCASE _DIGITS "_", line[end]))
		end++;
	str = ft_strndup(&line[start], end - start);
	if (str == NULL)
		return (NULL);
	*cursor = end - 1;
	return (msh_ast_tkn_new(TKN_WORD, str));
}
