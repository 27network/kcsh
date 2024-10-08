/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_transform_try_merge.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 01:00:21 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/07 17:33:52 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/transformer.h>
#include <msh/features.h>
#include <msh/log.h>
#include <msh/util.h>

#define IS_PATTERN msh_ast_token_is_subst_pattern

bool				msh_ast_token_is_subst_pattern(const t_ast_token *token);

t_ast_error			msh_ast_transform_merge_recurse(t_minishell *msh,
						t_list *const *tokens, bool *workret);

t_ast_token			*msh_ast_merge_pattopat(t_minishell *msh, t_list *token,
						const t_ast_token *current, const t_ast_token *next);
t_ast_token			*msh_ast_merge_pattostr(t_minishell *msh, t_list *token,
						const t_ast_token *current, const t_ast_token *next);
t_ast_token			*msh_ast_merge_pattow(t_minishell *msh, t_list *token,
						const t_ast_token *current, const t_ast_token *next);
t_ast_token			*msh_ast_merge_strtopat(t_minishell *msh, t_list *token,
						const t_ast_token *current, const t_ast_token *next);
t_ast_token			*msh_ast_merge_wtopat(t_minishell *msh, t_list *token,
						const t_ast_token *current, const t_ast_token *next);

t_ast_token			*msh_ast_merge_fdtoredir(t_minishell *msh, t_list *token,
						const t_ast_token *current, const t_ast_token *next);

t_ast_token			*msh_ast_merge_wtostr(t_minishell *msh, t_list *token,
						const t_ast_token *current, const t_ast_token *next);
t_ast_token			*msh_ast_merge_strtow(t_minishell *msh, t_list *token,
						const t_ast_token *current, const t_ast_token *next);
t_ast_token			*msh_ast_merge_wtow(t_minishell *msh, t_list *token,
						const t_ast_token *current, const t_ast_token *next);
t_ast_token			*msh_ast_merge_strtostr(t_minishell *msh, t_list *token,
						const t_ast_token *current, const t_ast_token *next);
t_ast_token			*msh_ast_merge_septosep(t_minishell *msh, t_list *token,
						const t_ast_token *current, const t_ast_token *next);

static t_ast_error	msh_ast_transform_try_merge_last(
	t_minishell *msh,
	t_list *token,
	t_ast_token *tokens[2],
	bool *work
) {
	t_ast_token			*new;
	const t_ast_token	*current = tokens[0];
	const t_ast_token	*next = tokens[1];

	new = NULL;
	if (next && current->type == TKN_NUMBER && next->type == TKN_REDIR
		&& FEAT_PARSER_42SH_REDIRS)
		new = msh_ast_merge_fdtoredir(msh, token, current, next);
	else
		return (msh_ast_err(AST_ERROR_CANCEL, false));
	if (new == NULL)
		return (msh_ast_errd(AST_ERROR_ALLOC, ": failed token merge", false));
	*work = true;
	return (msh_ast_ok());
}

static t_ast_error	msh_ast_transform_try_merge_others(
	t_minishell *msh,
	t_list *token,
	t_ast_token *tokens[2],
	bool *work
) {
	t_ast_token			*new;
	const t_ast_token	*current = tokens[0];
	const t_ast_token	*next = tokens[1];

	new = NULL;
	if (next && IS_PATTERN(current) && IS_PATTERN(next))
		new = msh_ast_merge_pattopat(msh, token, current, next);
	else if (next && IS_PATTERN(current) && next->type == TKN_STRING)
		new = msh_ast_merge_pattostr(msh, token, current, next);
	else if (next && current->type == TKN_STRING && IS_PATTERN(next))
		new = msh_ast_merge_strtopat(msh, token, current, next);
	else
		return (msh_ast_err(AST_ERROR_CANCEL, false));
	if (new == NULL)
		return (msh_ast_errd(AST_ERROR_ALLOC, ": failed token merge", false));
	*work = true;
	return (msh_ast_ok());
}

static t_ast_error	msh_ast_transform_try_merge_known(
	t_minishell *msh,
	t_list *token,
	t_ast_token *tokens[2],
	bool *w
) {
	const t_ast_token	*current = tokens[0];
	const t_ast_token	*next = tokens[1];
	t_ast_token			*new;

	new = NULL;
	if (next && current->type == TKN_STRING && next->type == TKN_WORD)
		new = msh_ast_merge_strtow(msh, token, current, next);
	else if (next && current->type == TKN_WORD && next->type == TKN_WORD)
		new = msh_ast_merge_wtow(msh, token, current, next);
	else if (next && current->type == TKN_WORD && next->type == TKN_STRING)
		new = msh_ast_merge_wtostr(msh, token, current, next);
	else if (next && current->type == TKN_STRING && next->type == TKN_STRING)
		new = msh_ast_merge_strtostr(msh, token, current, next);
	else if (next && current->type == TKN_SEP && next->type == TKN_SEP)
		new = msh_ast_merge_septosep(msh, token, current, next);
	else if (current->type == TKN_STRING && current->value.list)
		return (msh_ast_transform_merge_recurse(msh, &current->value.list, w));
	else
		return (msh_ast_err(AST_ERROR_CANCEL, false));
	if (new == NULL)
		return (msh_ast_errd(AST_ERROR_ALLOC, ": failed token merge", false));
	*w = true;
	return (msh_ast_ok());
}

/**
 * Basically we want to merge two tokens (list nodes) into one.
 *
 * We'll usually get the value of a token, or perhaps the entire token itself.
 * This means that we delegate the freeing logic to the merging function
 * entirely, including the list node.
 */
t_ast_error	msh_ast_transform_try_merge(t_minishell *msh,
				t_list *token, bool *work, size_t order)
{
	t_ast_token	*current;
	t_ast_token	*next;
	t_ast_error	ret;

	if (!token || !token->content)
		return (msh_ast_ok());
	current = token->content;
	next = NULL;
	if (token->next && token->next->content)
		next = token->next->content;
	*work = false;
	ret = msh_ast_transform_try_merge_known(msh, token,
			(t_ast_token *[2]){current, next}, work);
	if (ret.type == AST_ERROR_CANCEL)
		ret = msh_ast_transform_try_merge_others(msh, token,
				(t_ast_token *[2]){current, next}, work);
	if (ret.type == AST_ERROR_CANCEL && order > 3)
		ret = msh_ast_transform_try_merge_last(msh, token,
				(t_ast_token *[2]){current, next}, work);
	if (ret.type == AST_ERROR_NONE)
		*work = true;
	if (ret.type == AST_ERROR_CANCEL)
		return (msh_ast_ok());
	return (ret);
}
