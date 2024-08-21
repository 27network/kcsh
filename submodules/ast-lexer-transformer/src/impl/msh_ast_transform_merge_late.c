/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_transform_merge_late.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:22:33 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/29 18:03:18 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/sanitizer.h>
#include <msh/log.h>
#include <msh/util.h>

static t_ast_error	msh_ast_sanitize_merge_loop(t_minishell *msh,
						t_list **tokens, bool *workret);

t_ast_token			*msh_ast_merge_late_redirtostring(t_list *current,
						t_ast_token *redir, t_ast_token *string);

static t_ast_error	msh_ast_sanitize_try_merge_others(
	t_minishell *msh,
	t_ast_token *current,
	bool *work
) {
	if (current->type == TKN_STRING && current->value.list)
		return (msh_ast_sanitize_merge_loop(msh, &current->value.list, work));
	return (msh_ast_ok());
}

static bool	msh_ast_sanitize_try_merge_known(
	t_list *token,
	t_ast_token *current,
	t_ast_token *next,
	t_ast_token **new
) {
	*new = NULL;
	if (next && current->type == TKN_REDIR && next->type == TKN_STRING && (
			current->value.redir.right_word == NULL
			|| current->value.redir.right_fd == -1))
		*new = msh_ast_merge_late_redirtostring(token, current, next);
	return (*new == NULL);
}

/**
 * Basically we want to merge two tokens (list nodes) into one.
 *
 * We'll usually get the value of a token, or perhaps the entire token itself.
 * This means that we delegate the freeing logic to the merging function
 * entirely, including the list node.
 */
static t_ast_error	msh_ast_sanitize_try_merge(t_minishell *msh, t_list *token,
						bool *work)
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
	if (msh_ast_sanitize_try_merge_known(token, current, next, &new))
		return (msh_ast_sanitize_try_merge_others(msh, current, work));
	msh_log(msh, MSG_DEBUG_AST_SANITIZER, "sanitize_mergel: ");
	if (msh->flags.debug_sanitizer)
	{
		msh_ast_token_print(msh, new);
		msh_ast_token_print(msh, current);
		printf(" = ");
		msh_ast_token_print(msh, next);
		printf("\n");
	}
	*work = true;
	if (!new)
		return (msh_ast_errd(AST_ERROR_ALLOC, ": failed token merge", false));
	return (msh_ast_ok());
}

static t_ast_error	msh_ast_sanitize_merge_loop(t_minishell *msh,
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
		err = msh_ast_sanitize_try_merge(msh, current, &work);
		if (work)
			*workret = true;
		if (err.type != AST_ERROR_NONE)
			break ;
		current = current->next;
	}
	return (err);
}

t_ast_error	msh_ast_sanitize_merge_late(
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
		err = msh_ast_sanitize_merge_loop(msh, tokens, &work);
		if (err.type != AST_ERROR_NONE)
			break ;
		if (!work)
			break ;
	}
	return (err);
}
