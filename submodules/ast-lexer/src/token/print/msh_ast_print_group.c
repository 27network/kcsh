/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_print_group.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 12:21:46 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/21 17:03:14 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define __DUMB_LIBFT_FIX
#include <msh/ast/lexer/tokens.h>
#include <msh/ast/lexer/kinds.h>
#include <stdio.h>

void	msh_ast_token_print0(t_ast_token *token);

static void	msh_ast_token_print_list(t_ast_token *token)
{
	if (!token)
		return ;
	msh_ast_token_print0(token);
	printf(" ");
}

void	msh_ast_print_group(t_ast_token *token)
{
	if (!token || !token->value.list)
		return ;
	printf("( ");
	ft_lst_foreach(token->value.list,
		(t_list_foreach_fn *) msh_ast_token_print_list);
	printf(")");
}
