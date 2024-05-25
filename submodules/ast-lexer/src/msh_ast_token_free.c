/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 10:05:17 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/25 10:45:06 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <msh/ast/lexer.h>

void	msh_ast_token_free(t_ast_token *token)
{
	if (!token)
		return ;
	if (token->value)
		free(token->value);
	free(token);
}
