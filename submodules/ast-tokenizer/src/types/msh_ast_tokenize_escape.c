/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_tokenize_escape.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 20:10:54 by kiroussa          #+#    #+#             */
/*   Updated: 2024/03/22 22:10:24 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#define TOKENIZER_TYPES
#include <msh/ast/tokenizer.h>

t_token	*msh_ast_tokenize_escape(const char *line, size_t *cursor)
{
	char	c;
	char	*str;

	c = line[*cursor + 1];
	if (c == 0)
		return (msh_ast_tkn_new(TKN_EOF, NULL));
	str = ft_calloc(2, sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = c;
	*cursor += 1;
	return (msh_ast_tkn_new(TKN_WORD, str));
}
