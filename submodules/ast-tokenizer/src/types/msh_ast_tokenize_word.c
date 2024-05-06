/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_tokenize_word.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:49:21 by kiroussa          #+#    #+#             */
/*   Updated: 2024/03/07 08:12:59 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#define TOKENIZER_TYPES
#include <msh/ast/tokenizer.h>
#include <msh/features.h>

t_token	*msh_ast_tokenize_word(const char *line, size_t *cursor)
{
	size_t	start;
	size_t	end;
	char	*str;

	start = *cursor;
	end = start;
	while (line[end] && ft_strchr(TOKEN_DELIMITERS, line[end]) == NULL)
		end++;
	str = ft_strndup(&line[start], end - start);
	if (str == NULL)
		return (NULL);
	*cursor = end - 1;
	return (msh_ast_tkn_new(TKN_WORD, str));
}
