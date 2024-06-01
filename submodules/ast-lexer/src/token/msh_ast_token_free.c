/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 10:05:17 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/01 22:01:35 by kiroussa         ###   ########.fr       */
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
	else
		printf("Unfree'd token contents\n");
	free(token);
}
