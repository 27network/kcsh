/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_tokenize_string.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:44:46 by kiroussa          #+#    #+#             */
/*   Updated: 2024/03/23 03:12:19 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/features.h>
#define TOKENIZER_TYPES
#include <msh/ast/tokenizer.h>
#include <stdlib.h>

static size_t	msh_find_string_end(const char *line, size_t start)
{
	size_t	end;
	char	start_char;

	end = start + 1;
	start_char = line[start];
	while (line[end])
	{
		if (line[end] == '\\' && FEAT_PARSER_INHIBITORS)
			end++;
		else if (line[end] == start_char)
			break ;
		end++;
	}
	return (end);
}

t_token	*msh_ast_tokenize_string(const char *line, size_t *cursor)
{
	t_token	*token;
	size_t	start;
	size_t	end;
	char	*str;

	start = *cursor;
	end = msh_find_string_end(line, start);
	if (line[end] == '\0')
		return (NULL);
	str = ft_strndup(&line[start], end - start + 1);
	if (str == NULL)
		return (NULL);
	token = msh_ast_tkn_new(TKN_WORD, str);
	if (token == NULL)
	{
		free(str);
		return (NULL);
	}
	*cursor = end;
	return (token);
}
