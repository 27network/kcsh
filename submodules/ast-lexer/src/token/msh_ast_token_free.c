/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 10:05:17 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/03 21:06:19 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <msh/ast/lexer/tokens.h>
#include <stdio.h>

void	msh_ast_token_free(t_ast_token *token)
{
	if (!token)
		return ;
	if (token->value.string && (token->type == TKN_WORD
			|| token->type == TKN_SEP || token->type == TKN_COMMENT))
		free(token->value.string);
	else if (token->value.list && (token->type == TKN_GROUP
			|| token->type == TKN_STRING))
		ft_lst_free(&token->value.list, (t_lst_dealloc) msh_ast_token_free);
	else if (token->type == TKN_DELIM || token->type == TKN_PIPE
		|| token->type == TKN_SEMISEMI || token->type == TKN_KEYWORD)
	{
	}
	else
		printf("Unfree'd token contents (type: %s)\n",
			msh_ast_strtoken(token->type));
	free(token);
}
