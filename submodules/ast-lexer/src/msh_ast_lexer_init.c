/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_lexer_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 07:35:56 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/25 09:02:04 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/lexer.h>
#include <stddef.h>

void	msh_ast_lexer_init(t_ast_lexer *state, t_minishell *msh,
			const char *line)
{
	state->msh = msh;
	state->input = line;
	state->cursor = 0;
	state->token_start = 0;
	state->token_end = 0;
	state->tokens = NULL;
}
