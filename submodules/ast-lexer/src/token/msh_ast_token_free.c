/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 10:05:17 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/30 14:29:57 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <ft/mem.h>
#include <limits.h>
#include <msh/ast/lexer.h>
#include <stdint.h>
#include <stdio.h>

static void	msh_ast_token_free_redir(t_ast_token *redir)
{
	if (redir->value.redir.state == REDIR_STATE_WORD)
	{
		ft_lst_free(&redir->value.redir.right_word,
			(t_lst_dealloc) msh_ast_token_free);
		ft_strdel(&redir->value.redir.right_string);
	}
}

void	msh_ast_token_free(t_ast_token *token)
{
	if (!token || (uint64_t) token <= 10 || (uint64_t) token >= ULLONG_MAX - 10)
		return ;
	if (!token->value.data)
		(void) token->value.data;
	else if (token->type == TKN_SUBST || token->type == TKN_WORD
		|| token->type == TKN_SEP || token->type == TKN_COMMENT
		|| token->type == TKN_NUMBER)
		ft_strdel(&token->value.string);
	else if (token->type == TKN_GROUP || token->type == TKN_STRING)
		ft_lst_free(&token->value.list, (t_lst_dealloc) msh_ast_token_free);
	else if (token->type == TKN_REDIR)
		msh_ast_token_free_redir(token);
	else if (token->type == TKN_DELIM || token->type == TKN_PIPE
		|| token->type == TKN_SEMISEMI || token->type == TKN_KEYWORD)
	{
	}
	else
		printf("Unfree'd token contents (type: %s)\n",
			msh_ast_strtoken(token->type));
	free(token);
}
