/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_transform_substitute_tilde.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 07:40:33 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/28 18:01:41 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/ast/transformer.h>
#include <msh/env.h>
#include <msh/log.h>
#include <msh/util.h>
#include <stdio.h>
#include <stdlib.h>

#define LEVEL MSG_DEBUG_EXEC_TRANSFORMER

static t_ast_error	msh_ast_transform_tilde_target(t_minishell *msh,
						t_ast_token *tkn)
{
	char		*value;
	char		*new_val;

	if (tkn->type != TKN_SUBST || tkn->kind != SUBST_TILDE)
		return (msh_ast_ok());
	value = tkn->value.string;
	if (!value)
		return (msh_ast_ok());
	printf("tilde expansion: %s\n", value);
	new_val = msh_expand_tilde(msh, value);
	printf("tilde expansion (LE RETOUR): %s\n", new_val);
	if (!new_val)
		return (msh_ast_errd(AST_ERROR_ALLOC,
				": failed tilde expansion", false));
	tkn->value.string = new_val;
	tkn->type = TKN_WORD;
	free(value);
	return (msh_ast_ok());
}

t_ast_error	msh_ast_transform_substitute_tilde(t_minishell *msh,
				t_list **tokens, size_t order)
{
	t_ast_error	err;
	t_list		*token;
	t_list		*last;
	t_ast_token	*tkn;

	(void) order;
	if (!tokens || !*tokens)
		return (msh_ast_ok());
	last = NULL;
	msh_log(msh, LEVEL, "transform_substitute_tilde %p\n", *tokens);
	token = *tokens;
	err = msh_ast_ok();
	while (!err.type && token)
	{
		tkn = (t_ast_token *)token->content;
		if (tkn->type == TKN_SUBST && tkn->kind == SUBST_TILDE
			&& (!last || (last->content
					&& ((t_ast_token *)last->content)->type == TKN_SEP)))
			err = msh_ast_transform_tilde_target(msh, tkn);
		if (err.type != AST_ERROR_NONE)
			break ;
		last = token;
		token = token->next;
	}
	return (err);
}
