/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_sanitize_tokens.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:04:58 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/19 04:52:53 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#define MSH_SANITIZER_TYPE t_list
#include <msh/ast/sanitizer.h>
#include <msh/log.h>
#include <msh/util.h>

const char	*msh_syntax_error(t_ast_token *token);

t_ast_error	msh_ast_sanitize_token_dropseps(t_minishell *msh,
				t_list *current, t_ast_token *prev_tkn);
t_ast_error	msh_ast_sanitize_token_duplicate(t_minishell *msh, t_list *current);
t_ast_error	msh_ast_sanitize_token_first(t_minishell *msh, t_list *current,
				t_ast_token *token);
t_ast_error	msh_ast_sanitize_token_recurse(t_minishell *msh, t_list *current,
				t_ast_token *token);
t_ast_error	msh_ast_sanitize_token_word_before(t_minishell *msh,
				t_list *current, t_ast_token *prev_tkn);

static t_ast_error	msh_ast_sanitize_check(
	t_minishell *msh,
	t_list *current,
	t_ast_token *prev,
	t_ast_token *curr
) {
	t_ast_error	err;

	msh_log(msh, MSG_DEBUG_TOKEN_SANITIZER, "sanitize_check: ");
	if (msh->flags.debug_token_sanitizer)
		msh_ast_token_print(msh, curr);
	if (!prev)
		err = msh_ast_sanitize_token_first(msh, current, curr);
	if (err.type == AST_ERROR_NONE)
		err = msh_ast_sanitize_token_duplicate(msh, current);
	if (prev && err.type == AST_ERROR_NONE)
	{
		err = msh_ast_sanitize_token_word_before(msh, current, prev);
		if (err.type == AST_ERROR_NONE)
			err = msh_ast_sanitize_token_dropseps(msh, current, prev);
	}
	if (err.type == AST_ERROR_NONE)
		err = msh_ast_sanitize_token_recurse(msh, current, curr);
	return (err);
}

static bool	msh_ast_sanitize_skip_leading(t_list *current, t_list **nextret)
{
	t_ast_token	*tkn;
	bool		ret;

	*nextret = NULL;
	if (current == NULL)
		return (false);
	*nextret = current->next;
	tkn = (t_ast_token *) current->content;
	if (!tkn)
		return (false);
	ret = tkn->type == TKN_SEP;
	if (ret)
		ft_lst_delete(current, (t_lst_dealloc) msh_ast_token_free);
	return (ret);
}

static bool	msh_ast_sanitize_should_skip(t_list *current, t_list **tokens)
{
	t_ast_token	*tkn;

	if (!current || !tokens)
		return (true);
	if (current->next != NULL)
		return (false);
	tkn = (t_ast_token *) current->content;
	if (!tkn)
		return (false);
	if (tkn->type == TKN_DELIM && tkn->kind == DELIM_NEWLINE)
	{
		ft_lst_free(tokens, (t_lst_dealloc) msh_ast_token_free);
		return (true);
	}
	return (false);
}

static t_ast_error	msh_ast_sanitize_tokens_impl(t_minishell *msh, t_list *current)
{
	t_ast_token	*prevt;
	t_ast_error	err;

	prevt = NULL;
	err = msh_ast_ok();
	while (current && current->content && err.type == AST_ERROR_NONE)
	{
		err = msh_ast_sanitize_check(msh, current, prevt, current->content);
		msh_log(msh, MSG_DEBUG_TOKEN_SANITIZER, "got error? %s\n",
			msh_strbool(err.type != 0));
		if (current && current->content)
			prevt = current->content;
		current = current->next;
	}
	return (err);
}

t_ast_error	msh_ast_sanitize_tokens(
	t_minishell *msh,
	t_list **tokens
) {
	t_ast_error	err;
	t_list		*current;
	t_list		*next;
	t_list		*last_non_sep;

	current = *tokens;
	while (current && msh_ast_sanitize_skip_leading(current, &next))
		current = next;
	*tokens = current;
	if (msh_ast_sanitize_should_skip(current, tokens))
		return (msh_ast_err(AST_ERROR_CANCEL, false));
	err = msh_ast_sanitize_tokens_impl(msh, current);
	if (err.type == AST_ERROR_NONE)
	{
		next = current;
		last_non_sep = current;
		while (next && next->next)
		{
			next = next->next;
			if (((t_ast_token *) next->content)->type != TKN_SEP)
				last_non_sep = next;
		}
		ft_lst_free(&last_non_sep->next, (t_lst_dealloc) msh_ast_token_free);
	}
	return (err);
}
