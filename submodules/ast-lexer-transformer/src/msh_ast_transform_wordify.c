/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_transform_wordify.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:56:31 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/30 04:36:32 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/data/list.h>
#include <ft/mem.h>
#include <ft/string.h>
#include <msh/ast/transformer.h>
#include <msh/ast/lexer.h>

t_ast_error	msh_ast_transform_wordify(
				__attribute__((unused)) t_minishell *msh,
				t_list **tokens,
				__attribute__((unused)) size_t order
				);

static size_t	msh_ast_find_length(t_list *tokens)
{
	size_t		len;
	t_ast_token	*tkn;

	len = 0;
	while (tokens)
	{
		tkn = tokens->content;
		if (tkn && tkn->value.string)
			len += ft_strlen(tkn->value.string);
		tokens = tokens->next;
	}
	return (len);
}

static t_ast_error	msh_ast_transform_to_string(t_ast_token *token)
{
	char			*str;
	const size_t	len = msh_ast_find_length(token->value.list);
	t_list			*current;
	t_ast_token		*tkn;

	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (msh_ast_errd(AST_ERROR_ALLOC, "transform_to_string: couldn't "
				"allocate memory for string", false));
	current = token->value.list;
	while (current)
	{
		tkn = (t_ast_token *)current->content;
		if (tkn && tkn->value.string)
			ft_strlcat(str, tkn->value.string, len + 1);
		current = current->next;
	}
	ft_lst_free(&token->value.list, (t_lst_dealloc) msh_ast_token_free);
	token->value.string = str;
	token->type = TKN_WORD;
	return (msh_ast_ok());
}

static t_ast_error	msh_ast_transform_try_wordify(t_list *node)
{
	t_ast_token	*token;
	t_ast_error	err;

	token = node->content;
	err = msh_ast_ok();
	if (token && token->type == TKN_NUMBER)
		token->type = TKN_WORD;
	else if (token && token->type == TKN_STRING)
	{
		err = msh_ast_transform_wordify(NULL, &token->value.list, 0);
		if (err.type == AST_ERROR_NONE)
			err = msh_ast_transform_to_string(token);
	}
	return (err);
}

t_ast_error	msh_ast_transform_wordify(
	__attribute__((unused)) t_minishell *msh,
	t_list **tokens,
	__attribute__((unused)) size_t order
) {
	t_list		*current;
	t_ast_error	err;

	if (!tokens || !*tokens)
		return (msh_ast_ok());
	current = *tokens;
	err = msh_ast_ok();
	while (current && err.type == AST_ERROR_NONE)
	{
		if (current->content)
			err = msh_ast_transform_try_wordify(current);
		current = current->next;
	}
	return (err);
}
