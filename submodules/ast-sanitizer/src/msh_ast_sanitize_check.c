/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_sanitize_check.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:04:58 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/22 18:02:48 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <msh/ast/sanitizer.h>

const char	*msh_syntax_error(t_ast_token *token);

static t_ast_error	msh_ast_sanitize_check_duplicate(t_list *current)
{
	static const t_ast_token_type	no_dupes[] = {
		TKN_PIPE, TKN_AMP, TKN_DELIM, TKN_SEMISEMI
	};
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

#  include <stdio.h>

static t_ast_error	msh_ast_sanitize_check_first(
	t_list *current,
	t_ast_token *token
) {
	if (!current || !token)
		return (msh_ast_ok());
	if (token->type == TKN_PIPE || token->type == TKN_AMP || token->type
		== TKN_DELIM || token->type == TKN_SEMISEMI)
		return (msh_ast_errd(AST_ERROR_SYNTAX, (void *)msh_syntax_error(
					token), false));
	return (msh_ast_ok());
}

static t_ast_error	msh_ast_sanitize_check_word_before(
	t_list *current,
	t_list *prev,
	t_ast_token *curr_tkn,
	t_ast_token *prev_tkn
) {
	static const t_ast_token_type	no_first[] = {
		TKN_PIPE, TKN_AMP, TKN_DELIM, TKN_SEMISEMI
	};
	int								i;

	if (!current || !prev->content || !current->content)
		return (msh_ast_ok());
	if (!prev)
		return (msh_ast_sanitize_check_first(current, curr_tkn));
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
							(t_ast_token *) prev->content), false));
		}
	}
	return (msh_ast_ok());
}

t_ast_error	msh_ast_sanitize_check(
	__attribute__((unused)) t_minishell *msh,
	t_list **tokens
) {
	t_list		*current;
	t_list		*prev;
	t_ast_token	*currt;
	t_ast_token	*prevt;
	t_ast_error	err;

	current = *tokens;
	prev = NULL;
	err = msh_ast_ok();
	while (current && current->content && err.type == AST_ERROR_NONE)
	{
		err = msh_ast_sanitize_check_duplicate(current);
		if (err.type != AST_ERROR_NONE)
			break ;
		currt = current->content;
		prevt = NULL;
		if (prev)
			prevt = prev->content;
		err = msh_ast_sanitize_check_word_before(current, prev, currt, prevt);
		if (err.type != AST_ERROR_NONE)
			break ;
		prev = current;
		current = current->next;
	}
	return (err);
}
