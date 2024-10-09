/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_transform_run_pattern_matching.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 21:01:47 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/09 02:31:58 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <msh/ast/transformer.h>
#include <msh/env.h>
#include <msh/log.h>

t_ast_error	msh_pattern_match(t_minishell *msh, const char *pattern,
				t_list **match_stack);
const char	*msh_ast_transform_pattern_build_str(t_list *tokens);

static t_ast_error	msh_ast_transform_pattern_add_sep(t_minishell *msh,
						t_list **tokens)
{
	t_ast_error	err;
	t_ast_token	*tkn;

	(void) msh;
	err = msh_ast_token_new(TKN_SEP, &tkn);
	if (err.type)
		return (err);
	tkn->value.string = ft_strdup(" ");
	if (!tkn->value.string)
	{
		msh_ast_token_free(tkn);
		return (msh_ast_errd(AST_ERROR_ALLOC, NULL, false));
	}
	ft_lst_tadd(tokens, tkn);
	return (msh_ast_ok());
}

static t_ast_error	msh_ast_transform_to_token(
	__attribute__((unused)) t_minishell *msh,
						const char *match, t_list **tokens)
{
	t_ast_error	err;
	t_ast_token	*tkn;

	err = msh_ast_token_new(TKN_WORD, &tkn);
	if (err.type)
		return (err);
	tkn->value.string = ft_strdup(match);
	if (!tkn->value.string)
	{
		msh_ast_token_free(tkn);
		return (msh_ast_errd(AST_ERROR_ALLOC, NULL, false));
	}
	ft_lst_tadd(tokens, tkn);
	return (msh_ast_ok());
}

static t_ast_error	msh_ast_transform_to_tokens(t_minishell *msh,
				t_list *matches, t_list **tokens)
{
	t_ast_error	err;
	t_list		*current;
	t_list		*buffer;

	err = msh_ast_ok();
	current = matches;
	while (current)
	{
		buffer = current;
		if (!err.type)
			err = msh_ast_transform_to_token(msh, current->content, tokens);
		current = current->next;
		if (current)
			err = msh_ast_transform_pattern_add_sep(msh, tokens);
		ft_lst_delete(buffer, (t_lst_dealloc) free);
	}
	if (err.type)
		ft_lst_free(tokens, (t_lst_dealloc) msh_ast_token_free);
	return (err);
}

static t_ast_error	msh_ast_transform_pattern_match_impl(t_minishell *msh,
				t_list **tokens)
{
	t_ast_error	err;
	t_list		*match_stack;
	const char	*pattern;

	match_stack = NULL;
	if (!ft_lst_tadd(&match_stack, NULL))
		return (msh_ast_errd(AST_ERROR_ALLOC, NULL, false));
	pattern = msh_ast_transform_pattern_build_str(*tokens);
	if (!pattern)
		free(match_stack);
	if (!pattern)
		return (msh_ast_errd(AST_ERROR_ALLOC, NULL, false));
	err = msh_pattern_match(msh, pattern, &match_stack);
	ft_strdel((char **) &pattern);
	if (err.type)
		return (err);
	if (!match_stack)
		return (msh_ast_ok());
	ft_lst_free(tokens, (t_lst_dealloc)msh_ast_token_free);
	return (msh_ast_transform_to_tokens(msh, match_stack, tokens));
}

t_ast_error	msh_ast_transform_run_pattern_matching(t_minishell *msh,
				t_list **tokens)
{
	t_list		*current;
	t_ast_token	*token;
	t_ast_error	err;

	if (!msh_ast_token_rcount(*tokens, TKN_SUBST))
		return (msh_ast_ok());
	current = *tokens;
	err = msh_ast_ok();
	while (current)
	{
		token = (t_ast_token *)current->content;
		if (token->type == TKN_GROUP || token->type == TKN_STRING)
			err = msh_ast_transform_substitute_pattern(msh, &token->value.list,
					0);
		if (token->type == TKN_REDIR)
			err = msh_ast_transform_substitute_pattern(msh, &token->value.list,
					1);
		current = current->next;
	}
	if (!msh_ast_token_count(*tokens, TKN_SUBST))
		return (msh_ast_ok());
	err = msh_ast_transform_pattern_match_impl(msh, tokens);
	return (err);
}
