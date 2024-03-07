/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_tkn_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 04:42:13 by kiroussa          #+#    #+#             */
/*   Updated: 2024/03/07 06:39:26 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/tokenizer.h>
#include <stdlib.h>

void	msh_ast_tkn_free(t_token *token)
{
	if (!token)
		return ;
	if (token->data)
	{
		if (token->type == TKN_ASSIGNMENT_WORD)
		{
			free(((t_tkn_assign_data *)token->data)->key);
			free(((t_tkn_assign_data *)token->data)->value);
		}
		free(token->data);
	}
	free(token);
}
