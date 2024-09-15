/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_clone.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 23:28:37 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/15 23:34:46 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <msh/ast/lexer.h>

static bool	msh_ast_token_alloc(t_ast_token **token)
{
	*token = ft_calloc(1, sizeof(t_ast_token));
	return (*token != NULL);
}

t_ast_token	*msh_ast_token_clone(t_ast_token *token)
{
	t_ast_token	*clone;

	if (!msh_ast_token_alloc(&clone))
		return (NULL);
	ft_memcpy(clone, token, sizeof(t_ast_token));
	if (token->kind == TKN_GROUP)
	{
		clone->value.list = ft_lst_clone(token->value.list,
				(t_lst_dealloc) msh_ast_token_free);
		if (!clone->value.list)
		{
			msh_ast_token_free(clone);
			return (NULL);
		}
	}
	else if (token->value.string)
	{
		clone->value.string = ft_strdup(token->value.string);
		if (!clone->value.string)
		{
			msh_ast_token_free(clone);
			return (NULL);
		}
	}
	return (clone);
}
