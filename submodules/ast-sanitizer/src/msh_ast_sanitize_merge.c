/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_sanitize_merge.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:22:33 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/18 02:37:13 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/sanitizer.h>
#include <msh/util.h>

static t_ast_error	msh_ast_sanitize_merge_loop(t_list **tokens, bool *workret);

t_ast_token			*msh_ast_merge_wtostr(t_list *token, t_ast_token *current,
						t_ast_token *next);
t_ast_token			*msh_ast_merge_strtow(t_list *token, t_ast_token *current,
						t_ast_token *next);
t_ast_token			*msh_ast_merge_wtow(t_list *token, t_ast_token *current,
						t_ast_token *next);
t_ast_token			*msh_ast_merge_strtostr(t_list *token, t_ast_token *current,
						t_ast_token *next);

static t_ast_error	msh_ast_sanitize_try_merge_others(
	__attribute__((unused)) t_list *token,
	t_ast_token *current,
	__attribute__((unused)) t_ast_token *next,
	bool *work
) {
	if (current->type == TKN_STRING && current->value.list)
		return (msh_ast_sanitize_merge_loop(&current->value.list, work));
	return (msh_ast_ok());
}

/**
 * Basically we want to merge two tokens (list nodes) into one.
 *
 * We'll usually get the value of a token, or perhaps the entire token itself.
 * This means that we delegate the freeing logic to the merging function
 * entirely, including the list node.
 */
static t_ast_error	msh_ast_sanitize_try_merge(t_list *token, bool *work)
{
	t_ast_token	*current;
	t_ast_token	*next;
	t_ast_token	*new;

	if (!token || !token->content)
		return (msh_ast_ok());
	current = token->content;
	next = NULL;
	if (token->next && token->next->content)
		next = token->next->content;
	*work = false;
	if (next && current->type == TKN_STRING && (next->type == TKN_WORD || next->type == TKN_SUBST))
		new = msh_ast_merge_strtow(token, current, next);
	else if (next && current->type == TKN_WORD && next->type == TKN_WORD)
		new = msh_ast_merge_wtow(token, current, next);
	else if (next && (current->type == TKN_WORD || current->type == TKN_SUBST) && next->type == TKN_STRING)
		new = msh_ast_merge_wtostr(token, current, next);
	else if (next && current->type == TKN_STRING && next->type == TKN_STRING)
		new = msh_ast_merge_strtostr(token, current, next);
	else
		return (msh_ast_sanitize_try_merge_others(token, current, next, work));
	*work = true;
	if (!new)
		return (msh_ast_errd(AST_ERROR_ALLOC, ": failed token merge", false));
	return (msh_ast_ok());
}

static t_ast_error	msh_ast_sanitize_merge_loop(t_list **tokens, bool *workret)
{
	t_list		*current;
	t_ast_error	err;
	bool		work;

	current = *tokens;
	err = msh_ast_ok();
	while (current && err.type == AST_ERROR_NONE)
	{
		work = false;
		err = msh_ast_sanitize_try_merge(current, &work);
		if (work)
			*workret = true;
		if (err.type != AST_ERROR_NONE)
			break ;
		current = current->next;
	}
	return (err);
}

t_ast_error	msh_ast_sanitize_merge(t_list **tokens)
{
	t_ast_error	err;
	bool		work;

	if (!tokens || !*tokens)
		return (msh_ast_ok());
	err = msh_ast_ok();
	while (err.type == AST_ERROR_NONE)
	{
		work = false;
		err = msh_ast_sanitize_merge_loop(tokens, &work);
		if (err.type != AST_ERROR_NONE)
			break ;
		if (!work)
			break ;
	}
	return (err);
}
