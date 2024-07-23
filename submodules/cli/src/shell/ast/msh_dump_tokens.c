/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_dump_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 22:33:55 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/22 12:22:49 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/lexer.h>
#include <stdio.h>

void	msh_dump_tokens(t_minishell *msh, t_list *tokens)
{
	t_ast_token	*token;

	if (msh && !msh->flags.debug_tokenizer && !msh->flags.debug_generic)
		return ;
	printf("\n>>> Token list: \n");
	if (!tokens)
		return ;
	while (tokens)
	{
		token = (t_ast_token *) tokens->content;
		if (token)
			msh_ast_token_print(msh, token);
		tokens = tokens->next;
	}
	printf("\n");
}
