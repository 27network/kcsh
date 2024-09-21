/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_transform_substitute.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 07:40:33 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/20 14:58:26 by emfriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/ast/transformer.h>
#include <msh/env.h>
#include <msh/log.h>

static t_list	*msh_ast_transform_subst_append_split(t_minishell *msh,
					t_list *tokens, t_ast_token *tkn, const char *ifs)
{
}

static t_list	*msh_ast_transform_subst_noifs(t_minishell *msh,
					t_list **next, t_list *tokens, const char *env_value)
{
	t_list		*new;
	t_ast_token	*new_tkn;
	t_ast_error	err;

	err = msh_ast_token_new(TKN_WORD, &new_tkn);
	if (err.type != AST_ERROR_NONE)
		return (NULL);
	new_tkn->value.string = ft_strdup(env_value);
	if (!new_tkn->value.string || !ft_lst_tadd(next, new_tkn))
	{
		msh_ast_token_free(new);
		return (NULL);
	}
	return (new);
}

static t_ast_error	msh_ast_transform_subst_append(t_minishell *msh,
					t_list **next, t_list *tokens, t_ast_token *tkn)
{
	char		*env;
	char		*ifs;
	t_list		*torepl;
	t_ast_error	err;

	ifs = msh_env_value(msh, "IFS");
	if (!ifs)
		ifs = ENV_DEFAULT_IFS;
	env = msh_env_value(msh, tkn->value.string);
	next = tokens->next;
	if (!env)
		ft_lst_delete(tokens, (t_lst_dealloc) msh_ast_token_free);
	if (!env)
		return (next);
	if (!*ifs)
		to_repl = msh_ast_transform_subst_noifs(msh, next, tokens, env);
	else
		to_repl = msh_ast_transform_subst_append_split(msh, tokens, tkn, ifs);
	return (msh_ast_ok());
}

// &tokens_list so we can replace the first one
// &current->next so we can replace the next one based on the next one
static t_ast_error	msh_ast_transform_subst_target(t_minishell *msh,
						t_list **target)
{
	t_list		*tokens;
	t_list		*next_backup;
	t_ast_token	*tkn;
	t_ast_error	err;

	tokens = *target;
	next_backup = tokens->next;
	tkn = (t_ast_token *)tokens->content;
	err = msh_ast_ok();
	if (tkn->type == TKN_SUBST && tkn->kind == SUBST_VAR)
		err = msh_ast_transform_subst_append(msh, target, tokens, tkn);
	if (err.type != AST_ERROR_NONE)
		return (err);
	ft_lst_last(*target)->next = next_backup;
	return (err);
}

t_ast_error	msh_ast_transform_substitute(t_minishell *msh, t_list **tokens)
{
	t_ast_error	err;
	t_list		*token;
	t_ast_token	*tkn;

	if (!tokens || !*tokens)
		return (msh_ast_ok());
	token = *tokens;
	err = msh_ast_transform_subst_target(msh, &token);
	if (err.type != AST_ERROR_NONE)
		return (err);
	*tokens = token;
	while (token && token->next)
	{
		tkn = (t_ast_token *)token->next->content;
		if (tkn->type == TKN_SUBST && tkn->kind == SUBST_VAR)
			err = msh_ast_transform_subst_target(msh, &token->next);
		if (err.type != AST_ERROR_NONE)
			return (err);
		token = token->next;
	}
	return (err);
}
