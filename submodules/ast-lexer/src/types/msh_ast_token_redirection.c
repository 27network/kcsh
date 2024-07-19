/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_redirection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:36:16 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/19 17:03:04 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <msh/ast/lexer.h>

static t_ast_redir_type	msh_ast_token_redirection_type(t_ast_lexer *state)
{
	const char	*line = &state->input[state->cursor];

	if (!line || !*line)
		return (-1);
	return (REDIR_IN);
}

t_ast_error	msh_ast_token_redirection(t_ast_lexer *state, t_ast_token **tokret,
				size_t *inc)
{
	t_ast_token			*token;
	t_ast_error			err;
	t_ast_redir_type	type;

	type = msh_ast_token_redirection_type(state);
	if ((int)type == -1)
		return (msh_ast_errd(AST_ERROR_UNEXPECTED, "msh_ast_token_redirection"
				": invalid redirection type", false));
	err = msh_ast_ok();
	(void) token;
	(void) type;
	(void) inc;
	(void) tokret;
	return (err);
}
