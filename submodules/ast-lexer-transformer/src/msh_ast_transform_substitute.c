/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_transform_substitute.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 07:40:33 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/24 20:04:07 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/ast/transformer.h>
#include <msh/env.h>
#include <msh/log.h>
#include <stdio.h>

#define LEVEL MSG_DEBUG_EXEC_TRANSFORMER

t_ast_error	msh_ast_transform_subst_var(t_minishell *msh, t_list **next,
				t_list *tokens, t_ast_token *tkn);
void		msh_dump_tokens(t_minishell *msh, t_list *tokens);

static t_ast_error	msh_ast_transform_subst_target(t_minishell *msh,
						t_list **target, t_ast_token *tkn, bool *rerun)
{
	t_list		*tokens;
	t_list		*next_backup;
	t_ast_error	err;

	if (tkn->type != TKN_SUBST)
		return (msh_ast_ok());
	msh_log(msh, LEVEL, "transform_subst_target %p (%p)\n", target, *target);
	tokens = *target;
	next_backup = tokens->next;
	err = msh_ast_ok();
	if (tkn->kind == SUBST_VAR)
		err = msh_ast_transform_subst_var(msh, target, tokens, tkn);
	else
		return (err);
	if (err.type != AST_ERROR_NONE)
		return (err);
	msh_log(msh, LEVEL, "after subst: (%p)\n", *target);
	tokens = ft_lst_last(*target);
	if (!tokens)
		*target = next_backup;
	else
		tokens->next = next_backup;
	if (rerun)
		*rerun = !tokens;
	return (err);
}

t_ast_error	msh_ast_transform_substitute(t_minishell *msh, t_list **tokens)
{
	t_ast_error	err;
	t_list		*token;
	t_ast_token	*tkn;
	bool		rerun;

	if (!tokens || !*tokens)
		return (msh_ast_ok());
	msh_log(msh, LEVEL, "transform_substitute %p\n", *tokens);
	tkn = (t_ast_token *)(*tokens)->content;
	rerun = false;
	err = msh_ast_transform_subst_target(msh, tokens, tkn, &rerun);
	if (rerun)
		return (msh_ast_transform_substitute(msh, tokens));
	token = *tokens;
	while (!err.type && token && token->next)
	{
		msh_log(msh, LEVEL, "transform_substitute_loop %p\n", token);
		tkn = (t_ast_token *)token->next->content;
		err = msh_ast_transform_subst_target(msh, &token->next, tkn, &rerun);
		if (err.type != AST_ERROR_NONE)
			break ;
		if (!rerun)
			token = token->next;
	}
	return (err);
}
