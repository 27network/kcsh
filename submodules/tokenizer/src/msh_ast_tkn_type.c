/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_tkn_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:16:10 by kiroussa          #+#    #+#             */
/*   Updated: 2024/04/26 17:24:52 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/tokenizer.h>

const char	*msh_ast_tkn_type(t_token_type type)
{
	static const char	*types[] = {
	[TKN_WORD] = "word", [TKN_SPACE] = "space", [TKN_PIPE] = "pipe",
	[TKN_SEMICOLON] = "semicolon", [TKN_EOF] = "eof", [TKN_DOLLAR] = "dollar",
	[TKN_AMP] = "ampersand", [TKN_NEWLINE] = "newline",
	[TKN_REDIR_OUT] = "redir_out", [TKN_REDIR_IN] = "redir_in",
	[TKN_LPAREN] = "lparen", [TKN_RPAREN] = "rparen", [TKN_LBRACE] = "lbrace",
	[TKN_RBRACE] = "rbrace", [TKN_LBRACKET] = "lbracket",
	[TKN_RBRACKET] = "rbracket", [TKN_ASSIGN] = "assign", [TKN_SUBST] = "subst",
	[TKN_ASSIGN_WORD] = "assign_word", [TKN_AND] = "and", [TKN_OR] = "or",
	[TKN_REDIR_APPEND] = "redir_append", [TKN_REDIR_HEREDOC] = "redir_heredoc",
	[TKN_FD_REF] = "fd_ref", [TKN_REDIR_OUT_CLOBBER] = "redir_out_clobber",
	[TKN_REDIR_HERESTR] = "redir_herestr", [TKN_REDIR_BOTH] = "redir_word"
	};

	if (type < 0 || type >= TKN_COUNT)
		return ("unknown");
	return (types[type]);
}
