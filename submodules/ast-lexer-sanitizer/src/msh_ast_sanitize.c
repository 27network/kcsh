/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_sanitize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:04:58 by kiroussa          #+#    #+#             */
/*   Updated: 2024/08/21 19:34:38 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <msh/ast/sanitizer.h>
#include <msh/log.h>
#include <msh/util.h>

const char	*msh_syntax_error(t_ast_token *token);

static t_ast_error	msh_ast_sanitize_check_duplicate(t_list *current)
{
	static const t_ast_token_type	no_dupes[] = {
		TKN_PIPE, TKN_AMP, TKN_DELIM, TKN_SEMISEMI};
	t_ast_token						*token;
	t_ast_token						*next;
	size_t							i;

	if (!current->next)
		return (msh_ast_ok());
	token = current->content;
	next = current->next->content;
	if (!token || !next)
		return (msh_ast_errd(AST_ERROR_ALLOC, "sanitize_check_dupes: "
				"empty token", false));
	if (token->type != next->type)
		return (msh_ast_ok());
	i = 0;
	while (i < sizeof(no_dupes) / sizeof(no_dupes[0]))
	{
		if (token->type == no_dupes[i])
			return (msh_ast_errd(AST_ERROR_SYNTAX, (void *)msh_syntax_error(
						token), false));
		i++;
	}
	return (msh_ast_ok());
}

static t_ast_error	msh_ast_sanitize_check_first(
	t_minishell *msh,
	t_list *current,
	t_ast_token *token
) {
	if (!current || !token)
		return (msh_ast_ok());
	msh_log(msh, MSG_DEBUG_AST_SANITIZER, "sanitize_check_first: ");
	if (msh->flags.debug_sanitizer)
		msh_ast_token_print(msh, token);
	if (token->type == TKN_PIPE || token->type == TKN_AMP || token->type
		== TKN_DELIM || token->type == TKN_SEMISEMI)
		return (msh_ast_errd(AST_ERROR_SYNTAX, (void *)msh_syntax_error(
					token), false));
	return (msh_ast_ok());
}

//TODO: fix this
static t_ast_error	msh_ast_sanitize_check_word_before(
	t_list *current,
	t_ast_token *prev_tkn
) {
	static const t_ast_token_type	no_first[] = {
		TKN_PIPE, TKN_AMP, TKN_DELIM, TKN_SEMISEMI};
	int								i;
	t_ast_token						*curr_tkn;

	if (!current || !current->content || !prev_tkn)
		return (msh_ast_ok());
	curr_tkn = current->content;
	i = -1;
	while (++i < (int)(sizeof(no_first) / sizeof(no_first[0])))
	{
		if (curr_tkn->type == no_first[i])
		{
			if (curr_tkn->type == TKN_DELIM && (curr_tkn->kind
					== DELIM_SEMICOLON || curr_tkn->kind == DELIM_NEWLINE))
				break ;
			if (prev_tkn->type != TKN_WORD && prev_tkn->type != TKN_STRING
				&& prev_tkn->type != TKN_GROUP && prev_tkn->type != TKN_SEP)
				return (msh_ast_errd(AST_ERROR_SYNTAX, (void *)msh_syntax_error(
							prev_tkn), false));
		}
	}
	return (msh_ast_ok());
}

static t_ast_error	msh_ast_sanitize_check(
	t_minishell *msh,
	t_list *current,
	t_ast_token *prev,
	t_ast_token *curr
) {
	t_ast_error	err;

	msh_log(msh, MSG_DEBUG_AST_SANITIZER, "sanitize_check: ");
	if (msh->flags.debug_sanitizer)
		msh_ast_token_print(msh, curr);
	if (!prev)
		err = msh_ast_sanitize_check_first(msh, current, curr);
	if (err.type != AST_ERROR_NONE)
		return (err);
	msh_log(msh, MSG_DEBUG_AST_SANITIZER, "sanitize_check_duplicate\n");
	err = msh_ast_sanitize_check_duplicate(current);
	if (err.type != AST_ERROR_NONE)
		return (err);
	msh_log(msh, MSG_DEBUG_AST_SANITIZER, "sanitize_check_word_before\n");
	err = msh_ast_sanitize_check_word_before(current, prev);
	return (err);
}

t_ast_error	msh_ast_sanitize(
	t_minishell *msh,
	t_list **tokens
) {
	t_list		*current;
	t_ast_token	*prevt;
	t_ast_error	err;

	current = *tokens;
	prevt = NULL;
	err = msh_ast_ok();
	while (current && current->content && err.type == AST_ERROR_NONE)
	{
		err = msh_ast_sanitize_check(msh, current, prevt, current->content);
		msh_log(msh, MSG_DEBUG_AST_SANITIZER, "got error? %s\n",
			msh_strbool(err.type != 0));
		if (current && current->content)
			prevt = current->content;
		current = current->next;
	}
	return (err);
}
