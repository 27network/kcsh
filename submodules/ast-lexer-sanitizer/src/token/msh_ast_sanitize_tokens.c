/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_sanitize_tokens.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:04:58 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/09 02:25:30 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#define MSH_SANITIZER_TYPE t_list
#include <msh/ast/sanitizer.h>
#include <msh/log.h>
#include <msh/util.h>

const char	*msh_syntax_error(t_ast_token *token);

t_ast_error	msh_ast_sanitize_check(
				t_minishell *msh,
				t_list *current,
				t_ast_token *prev,
				t_ast_token *curr
				);

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
	ret |= tkn->type == TKN_DELIM && tkn->kind == DELIM_NEWLINE;
	if (ret)
		ft_lst_delete(current, (t_lst_dealloc) msh_ast_token_free);
	return (ret);
}

static bool	msh_ast_sanitize_trailing_newlines(t_list **tokens, t_list *current)
{
	t_list		*last;
	t_list		*pre_last;
	t_ast_token	*tkn;

	*tokens = current;
	if (!tokens || !*tokens)
		return (false);
	last = *tokens;
	while (last && last->next && last->next->next)
		last = last->next;
	pre_last = last;
	last = last->next;
	if (!pre_last || !pre_last->content)
		return (false);
	tkn = (t_ast_token *) pre_last->content;
	if (!last && tkn->type == TKN_DELIM && tkn->kind == DELIM_NEWLINE)
		return (ft_lst_free(tokens, (t_lst_dealloc) msh_ast_token_free), 1);
	if (!last)
		return (false);
	tkn = (t_ast_token *) last->content;
	if (tkn->type == TKN_DELIM && tkn->kind == DELIM_NEWLINE)
		pre_last->next = NULL;
	if (tkn->type == TKN_DELIM && tkn->kind == DELIM_NEWLINE)
		ft_lst_delete(last, (t_lst_dealloc) msh_ast_token_free);
	return (false);
}

static t_ast_error	msh_ast_sanitize_tokens_impl(t_minishell *msh,
						t_list *current)
{
	t_ast_token	*prevt;
	t_ast_error	err;
	t_list		*next;

	prevt = NULL;
	err = msh_ast_ok();
	while (current && current->content && err.type == AST_ERROR_NONE)
	{
		next = current->next;
		err = msh_ast_sanitize_check(msh, current, prevt, current->content);
		msh_log(msh, MSG_DEBUG_TOKEN_SANITIZER, "got error? %s\n",
			msh_strbool(err.type != 0));
		if (current && current->content)
			prevt = current->content;
		current = next;
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
	if (msh_ast_sanitize_trailing_newlines(tokens, current))
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
		if (last_non_sep)
			ft_lst_free(&last_non_sep->next, (t_lst_dealloc)msh_ast_token_free);
	}
	return (err);
}
