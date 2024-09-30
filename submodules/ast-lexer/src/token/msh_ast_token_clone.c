/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_clone.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 23:28:37 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/30 14:29:43 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <msh/ast/lexer.h>
#include <stdio.h>

static bool	msh_ast_token_realloc(t_ast_token *tok, t_ast_token **token)
{
	t_ast_error	err;

	if (!tok)
		return (false);
	err = msh_ast_token_new(tok->type, token);
	if (err.type != AST_ERROR_NONE)
		return (false);
	ft_memcpy(*token, tok, sizeof(t_ast_token));
	return (true);
}

static void	msh_token_free(t_ast_token **token)
{
	if (!token || !*token)
		return ;
	msh_ast_token_free(*token);
	*token = NULL;
}

t_list	*msh_clone_tokens(t_minishell *msh, t_list *tokens);

static void	msh_token_clone_redir(t_ast_token *token, t_ast_token **clone)
{
	if (token->value.redir.state == REDIR_STATE_WORD)
	{
		(*clone)->value.redir.right_word = msh_clone_tokens(NULL,
				token->value.redir.right_word);
		if (token->value.redir.right_string)
			(*clone)->value.redir.right_string
				= ft_strdup(token->value.redir.right_string);
	}
}

t_ast_token	*msh_ast_token_clone(t_ast_token *token)
{
	t_ast_token	*clone;

	if (!msh_ast_token_realloc(token, &clone))
		return (NULL);
	if (token->value.list && (token->type == TKN_GROUP
			|| token->type == TKN_STRING))
	{
		clone->value.list = msh_clone_tokens(NULL, clone->value.list);
		if (!clone->value.list)
			msh_token_free(&clone);
	}
	else if (token->value.string && (token->type == TKN_SUBST
			|| token->type == TKN_WORD || token->type == TKN_SEP
			|| token->type == TKN_COMMENT || token->type == TKN_NUMBER))
	{
		clone->value.string = ft_strdup(token->value.string);
		if (!clone->value.string)
			msh_token_free(&clone);
	}
	else if (token->type == TKN_REDIR)
		msh_token_clone_redir(token, &clone);
	return (clone);
}

t_list	*msh_clone_tokens(
	__attribute__((unused)) t_minishell *msh,
	t_list *tokens
) {
	t_list		*cloned;
	t_ast_token	*clone;

	cloned = NULL;
	while (tokens)
	{
		clone = msh_ast_token_clone(tokens->content);
		if (!clone || !ft_lst_tadd(&cloned, clone))
		{
			free(clone);
			ft_lst_free(&cloned, (t_lst_dealloc) msh_ast_token_free);
			return (NULL);
		}
		tokens = tokens->next;
	}
	return (cloned);
}
