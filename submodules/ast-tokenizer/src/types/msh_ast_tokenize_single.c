/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_tokenize_single.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:49:41 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/17 02:23:22 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#define TOKENIZER_TYPES
#include <msh/ast/tokenizer.h>

#define _PARAN_TYPES "()[]{}"

t_token	*msh_ast_tokenize_single(const char *line, size_t *cursor)
{
	static t_token_type	char_to_type[] = {
	['('] = TKN_LPAREN, [')'] = TKN_RPAREN, ['['] = TKN_LBRACKET,
	[']'] = TKN_RBRACKET, ['{'] = TKN_LBRACE, ['}'] = TKN_RBRACE,
	[' '] = TKN_SPACE, ['\n'] = TKN_NEWLINE, [';'] = TKN_SEMICOLON,
	['|'] = TKN_PIPE, ['&'] = TKN_AMP, ['<'] = TKN_REDIR_IN,
	['>'] = TKN_REDIR_OUT, ['='] = TKN_ASSIGN, ['$'] = TKN_DOLLAR
	};

	return (msh_ast_tkn_new(char_to_type[(int) line[*cursor]], NULL));
}
