/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_transform_subst_var.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:59:09 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/09 02:06:03 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/ast/transformer.h>
#include <msh/env.h>
#include <msh/log.h>
#include <stdio.h>

#define LEVEL MSG_DEBUG_EXEC_TRANSFORMER

void	msh_dump_tokens(t_minishell *msh, t_list *tokens);

static t_ast_error	msh_ast_transform_subst_var_split(t_minishell *msh,
						t_list **next, const char *env, const char *ifs)
{
	const uint64_t	fork_level = msh->forked;
	t_ast_lexer		lexer;
	t_ast_error		err;

	msh->forked = 0;
	lexer = msh_ast_lexer_root(msh, env);
	lexer.ifs = ifs;
	lexer.discrim_mode = true;
	lexer.allow_subst = false;
	err = msh_ast_tokenize(&lexer);
	msh->forked = fork_level;
	if (err.type == AST_ERROR_NONE)
		*next = lexer.tokens;
	return (err);
}

static t_ast_error	msh_ast_transform_subst_noifs(
	__attribute__((unused)) t_minishell *msh,
						t_list **next, const char *env_value)
{
	t_list		*new;
	t_ast_token	*new_tkn;
	t_ast_error	err;

	err = msh_ast_token_new(TKN_WORD, &new_tkn);
	if (err.type != AST_ERROR_NONE)
		return (err);
	new = NULL;
	new_tkn->value.string = ft_strdup(env_value);
	if (!new_tkn->value.string || !ft_lst_tadd(&new, new_tkn))
	{
		msh_ast_token_free(new_tkn);
		return (msh_ast_errd(AST_ERROR_ALLOC,
				"couldn't allocate substitution string", false));
	}
	*next = new;
	return (msh_ast_ok());
}

t_ast_error	msh_ast_transform_subst_var(t_minishell *msh,
						t_list **next, t_list *tokens, t_ast_token *tkn)
{
	char		*env;
	char		*ifs;
	t_ast_error	err;

	ifs = msh_env_value(msh, "IFS");
	if (!ifs)
		ifs = ENV_DEFAULT_IFS;
	msh_log(msh, LEVEL, "transform_subst_var %p (%s)\n",
		tokens, tkn->value.string);
	env = msh_env_value(msh, tkn->value.string);
	if (!env)
	{
		ft_lst_delete(tokens, (t_lst_dealloc) msh_ast_token_free);
		*next = NULL;
		return (msh_ast_ok());
	}
	if (!*ifs)
		err = msh_ast_transform_subst_noifs(msh, next, env);
	else
		err = msh_ast_transform_subst_var_split(msh, next, env, ifs);
	if (err.type == AST_ERROR_NONE)
		ft_lst_delete(tokens, (t_lst_dealloc) msh_ast_token_free);
	else
		*next = NULL;
	return (err);
}
