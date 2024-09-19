/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_transform_merge.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:22:33 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/19 06:20:27 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/transformer.h>
#include <msh/log.h>
#include <msh/util.h>

static t_ast_error	msh_ast_transform_merge_loop(t_minishell *msh,
						t_list **tokens, bool *workret);

t_ast_token			*msh_ast_merge_fdtoredir(t_list *token,
						t_ast_token *current, t_ast_token *next);
t_ast_token			*msh_ast_merge_redirtosep(t_list *current,
						t_ast_token *redir, t_ast_token *sep);

t_ast_token			*msh_ast_merge_wtostr(t_minishell *msh, t_list *token,
						t_ast_token *current, t_ast_token *next);
t_ast_token			*msh_ast_merge_strtow(t_minishell *msh, t_list *token,
						t_ast_token *current, t_ast_token *next);
t_ast_token			*msh_ast_merge_wtow(t_minishell *msh, t_list *token,
						t_ast_token *current, t_ast_token *next);
t_ast_token			*msh_ast_merge_strtostr(t_minishell *msh, t_list *token,
						t_ast_token *current, t_ast_token *next);

static t_ast_error	msh_ast_transform_try_merge_others(
	t_minishell *msh,
	t_ast_token *current,
	bool *work
) {
	if (current->type == TKN_STRING && current->value.list)
		return (msh_ast_transform_merge_loop(msh, &current->value.list, work));
	return (msh_ast_ok());
}

#define MERGE_DONE	0
#define MERGE_NEXT	1
#define MERGE_FAIL	2

static int	msh_ast_transform_try_merge_known(
	t_minishell *msh,
	t_list *token,
	t_ast_token *current,
	t_ast_token *next
) {
	t_ast_token	*new;

	new = NULL;
	if (next && current->type == TKN_STRING && next->type == TKN_WORD)
		new = msh_ast_merge_strtow(msh, token, current, next);
	else if (next && current->type == TKN_WORD && next->type == TKN_WORD)
		new = msh_ast_merge_wtow(msh, token, current, next);
	else if (next && current->type == TKN_WORD && next->type == TKN_STRING)
		new = msh_ast_merge_wtostr(msh, token, current, next);
	else if (next && current->type == TKN_STRING && next->type == TKN_STRING)
		new = msh_ast_merge_strtostr(msh, token, current, next);
	// else if (next && current->type == TKN_NUMBER && next->type == TKN_REDIR)
	// 	*new = msh_ast_merge_fdtoredir(token, current, next);
	// else if (false && next && current->type == TKN_REDIR
	// 	&& next->type == TKN_SEP)
	// 	*new = msh_ast_merge_redirtosep(token, current, next);
	else
		return (MERGE_NEXT);
	if (new == NULL)
		return (MERGE_FAIL);
	return (MERGE_DONE);
}

/**
 * Basically we want to merge two tokens (list nodes) into one.
 *
 * We'll usually get the value of a token, or perhaps the entire token itself.
 * This means that we delegate the freeing logic to the merging function
 * entirely, including the list node.
 */
static t_ast_error	msh_ast_transform_try_merge(t_minishell *msh,
						t_list *token, bool *work)
{
	t_ast_token	*current;
	t_ast_token	*next;
	int			ret;

	if (!token || !token->content)
		return (msh_ast_ok());
	current = token->content;
	next = NULL;
	if (token->next && token->next->content)
		next = token->next->content;
	*work = false;
	ret = msh_ast_transform_try_merge_known(msh, token, current, next);
	if (ret == MERGE_NEXT)
		return (msh_ast_transform_try_merge_others(msh, current, work));
	*work = true;
	if (ret == MERGE_FAIL)
		return (msh_ast_errd(AST_ERROR_ALLOC, ": failed token merge", false));
	return (msh_ast_ok());
}

void				msh_dump_tokens(t_minishell *msh, t_list *tokens);

static t_ast_error	msh_ast_transform_merge_loop(t_minishell *msh,
						t_list **tokens, bool *workret)
{
	t_list		*current;
	t_ast_error	err;
	bool		work;

	current = *tokens;
	err = msh_ast_ok();
	while (current && err.type == AST_ERROR_NONE)
	{
		work = false;
		err = msh_ast_transform_try_merge(msh, current, &work);
		if (work)
			*workret = true;
		if (err.type != AST_ERROR_NONE)
			break ;
		current = current->next;
	}
	return (err);
}

t_ast_error	msh_ast_transform_merge(
	t_minishell *msh,
	t_list **tokens
) {
	t_ast_error	err;
	bool		work;

	if (!tokens || !*tokens)
		return (msh_ast_ok());
	err = msh_ast_ok();
	while (err.type == AST_ERROR_NONE)
	{
		work = false;
		err = msh_ast_transform_merge_loop(msh, tokens, &work);
		if (err.type != AST_ERROR_NONE)
			break ;
		if (!work)
			break ;
	}
	return (err);
}
