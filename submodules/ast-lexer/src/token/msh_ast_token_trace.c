/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_trace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:00:59 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/11 18:11:17 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/lexer.h>
#include <msh/log.h>

void	msh_ast_token_trace(t_ast_lexer *lexer, t_ast_token_type type,
			int state)
{
	char	*s;

	s = "Finished";
	if (state == 1)
		s = "Starting";
	if (state == 2)
		s = "Error for";
	msh_log(lexer->msh, MSG_DEBUG_TOKENIZER,
		"(%d) %s tokenization for %s\n",
		lexer->id, s, msh_ast_strtoken(type));
}
