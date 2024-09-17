/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_clone_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:49:43 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/17 16:07:01 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <msh/ast/builder.h>
#include <msh/log.h>

t_ast_token	*msh_ast_token_clone(t_ast_token *token);

t_list	*msh_clone_tokens(
	__attribute__((unused)) t_minishell *msh,
	t_list *tokens
) {
	t_list		*cloned;
	t_ast_token	*clone;

	cloned = NULL;
	while (tokens)
	{
		clone = msh_ast_token_clone(tokens->content);
		if (!clone || !ft_lst_tadd(&cloned, clone))
		{
			free(clone);
			ft_lst_free(&cloned, (t_lst_dealloc) msh_ast_token_free);
			return (NULL);
		}
		tokens = tokens->next;
	}
	return (cloned);
}
