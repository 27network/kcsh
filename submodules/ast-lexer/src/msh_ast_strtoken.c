/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_strtoken.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 06:53:13 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/25 06:55:28 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/tokens.h>

const char	*msh_ast_strtoken(t_ast_tkn_type type)
{
	static const char	*tkn_names[] = {
	[TKN_KEYWORD] = "keyword", [TKN_PIPE] = "pipe", [TKN_DELIM] = "delimiter",
	[TKN_REDIR] = "redirection", [TKN_STRING] = "string", [TKN_WORD] = "word",
	[TKN_SUBSTI] = "substitution", [TKN_NEWLINE] = "newline", [TKN_EOF] = "eof"
	};

	if (type < 0 || type > TKN_EOF)
		return ("unknown");
	return (tkn_names[type]);
}
