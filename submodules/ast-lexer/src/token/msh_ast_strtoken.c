/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_strtoken.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 06:53:13 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/21 17:04:59 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/lexer/tokens.h>

const char	*msh_ast_strtoken(t_ast_token_type type)
{
	static const char	*tkn_names[] = {
	[TKN_SEP] = "separator", [TKN_SPACE] = "space", [TKN_KEYWORD] = "keyword",
	[TKN_PIPE] = "pipe", [TKN_DELIM] = "delimiter", [TKN_REDIR] = "redirection",
	[TKN_SEMISEMI] = "dsemi", [TKN_GROUP] = "group", [TKN_COMMENT] = "comment",
	[TKN_STRING] = "string", [TKN_WORD] = "word", [TKN_SUBST] = "substitution",
	[TKN_EOF] = "eof", [TKN_AMP] = "amp", [TKN_NUMBER] = "number"
	};

	if (type < 0 || type > TKN_EOF)
		return ("unknown");
	return (tkn_names[type]);
}
