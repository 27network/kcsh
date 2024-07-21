/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_print_string.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 12:23:40 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/21 12:25:00 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/lexer.h>
#include <stdio.h>

void	msh_ast_print_string(t_ast_token *token)
{
	if (!token)
		return ;
	if (!token->value.string)
		printf("[empty]");
	else
		printf("(%s)", token->value.string);
}
