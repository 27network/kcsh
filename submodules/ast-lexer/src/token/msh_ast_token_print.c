/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_print.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 01:11:11 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/01 20:05:16 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define __DUMB_LIBFT_FIX
#include <msh/ast/lexer/tokens.h>
#include <msh/minishell.h>
#include <stdio.h>

static void	msh_ast_token_print0(t_ast_token *token);

static void	msh_ast_token_print_list(t_ast_token *token)
{
	msh_ast_token_print0(token);
	printf(" ");
}

static void	msh_ast_token_print0(t_ast_token *token)
{
	const char	*type = msh_ast_strtoken(token->type);

	printf("%s", type);
	if (token->type == TKN_KEYWORD)
		printf("( %s )", "insertkeywordhere");
	else if (token->type == TKN_STRING || token->type == TKN_GROUP)
	{
		printf("( ");
		ft_lst_foreach(token->value.list,
			(t_list_foreach_fn *) msh_ast_token_print_list);
		printf(")");
	}
	else if (token->type == TKN_WORD)
	{
		if (!token->value.string || !*token->value.string)
			printf("[empty]");
		else
			printf("( %s )", token->value.string);
	}
}

void	msh_ast_token_print(t_minishell *msh, t_ast_token *token)
{
	if (!msh->flags.debug_tokenizer)
		return ;
	msh_ast_token_print0(token);
	printf("\n");
}
