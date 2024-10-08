/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_strtoken_simple.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:58:25 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/05 04:04:00 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/lexer.h>

const char	*msh_ast_strdelim(t_ast_delim_type type);
const char	*msh_ast_strkeyword(t_ast_keyword_type type);
const char	*msh_ast_strredir(t_ast_redir_type type);

static const char	*msh_ast_strtoken_group(t_ast_group_type type,
						const char *paran)
{
	static const char	*types[] = {
	[GROUP_SUBSHELL] = "(\0)",
	[GROUP_BRACE] = "{\0}",
	};
	const char			*ret;

	ret = types[type];
	if (paran && *paran == ')')
		ret += 2;
	return (ret);
}

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
		return (msh_ast_strtoken_group(token->kind, paran));
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
