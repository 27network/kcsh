/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_transform_substitute_var.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 07:40:33 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/28 20:29:11 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/ast/transformer.h>
#include <msh/env.h>
#include <msh/log.h>
#include <stdio.h>

#define LEVEL MSG_DEBUG_EXEC_TRANSFORMER

t_ast_error	msh_ast_transform_substitute_var(t_minishell *msh, t_list **tokens,
				__attribute__((unused)) size_t order);
t_ast_error	msh_ast_transform_subst_var(t_minishell *msh, t_list **next,
				t_list *tokens, t_ast_token *tkn);
void		msh_dump_tokens(t_minishell *msh, t_list *tokens);

t_ast_error	msh_ast_transform_subst_wrap(t_minishell *msh, t_list **target,
				t_list *tokens, t_ast_token *tkn)
{
	t_ast_error	err;

	if (tkn->type == TKN_STRING)
	{
		if (tkn->value.list)
			err = msh_ast_transform_substitute_var(msh, &tkn->value.list, 0);
		else
			err = msh_ast_ok();
		(*target)->next = NULL;
		return (err);
	}
	return (msh_ast_transform_subst_var(msh, target, tokens, tkn));
}

static t_ast_error	msh_ast_transform_subst_target(t_minishell *msh,
						t_list **target, t_ast_token *tkn, bool *rerun)
{
	t_list		*tokens;
	t_list		*next_backup;
	t_ast_error	err;

	if (tkn->type != TKN_SUBST && tkn->type != TKN_STRING)
		return (msh_ast_ok());
	msh_log(msh, LEVEL, "transform_subst_target %p (%p)\n", target, *target);
	tokens = *target;
	next_backup = tokens->next;
	if (tkn->kind == SUBST_VAR || tkn->type == TKN_STRING)
		err = msh_ast_transform_subst_wrap(msh, target, tokens, tkn);
	else
		return (msh_ast_ok());
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

t_ast_error	msh_ast_transform_substitute_var(t_minishell *msh, t_list **tokens,
				__attribute__((unused)) size_t order)
{
	t_ast_error	err;
	t_list		*token;
	t_ast_token	*tkn;
	bool		rerun;

	if (!tokens || !*tokens)
		return (msh_ast_ok());
	tkn = (t_ast_token *)(*tokens)->content;
	rerun = false;
	err = msh_ast_transform_subst_target(msh, tokens, tkn, &rerun);
	if (rerun)
		return (msh_ast_transform_substitute_var(msh, tokens, 0));
	token = *tokens;
	while (!err.type && token && token->next)
	{
		msh_log(msh, LEVEL, "transform_substitute_loop %p\n", token);
		tkn = (t_ast_token *)token->next->content;
		rerun = false;
		err = msh_ast_transform_subst_target(msh, &token->next, tkn, &rerun);
		if (err.type != AST_ERROR_NONE)
			break ;
		if (!rerun)
			token = token->next;
	}
	return (err);
}
