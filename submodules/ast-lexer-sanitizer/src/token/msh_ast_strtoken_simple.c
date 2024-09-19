/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_strtoken_simple.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:58:25 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/19 07:34:18 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/lexer.h>

const char	*msh_ast_strdelim(t_ast_delim_type type);
const char	*msh_ast_strkeyword(t_ast_keyword_type type);
const char	*msh_ast_strredir(t_ast_redir_type type);

const char	*msh_ast_strtoken_simple_impl(t_ast_token *token, const char *paran)
{
	if (token->type == TKN_WORD)
		return (token->value.data);
	if (token->type == TKN_PIPE)
		return ("|");
	if (token->type == TKN_DELIM)
		return (msh_ast_strdelim(token->kind));
	if (token->type == TKN_SEMISEMI)
		return (";;");
	if (token->type == TKN_GROUP)
		return (paran);
	if (token->type == TKN_KEYWORD)
		return (msh_ast_strkeyword(token->kind));
	if (token->type == TKN_REDIR)
		return (msh_ast_strredir(token->kind));
	return (msh_ast_strtoken(token->type));
}

const char	*msh_ast_strtoken_simple(t_ast_token *token)
{
	return (msh_ast_strtoken_simple_impl(token, ")"));
}
