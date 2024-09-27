/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_transform_wordify.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:56:31 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/27 16:11:44 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/ast/transformer.h>

static t_ast_error	msh_ast_transform_to_string(t_ast_token *token)
{
	t_list		*list;
	t_ast_token	*new;

	list = NULL;
	new = msh_ast_token_clone(token);
	if (!new)
		return (msh_ast_errd(AST_ERROR_ALLOC, ": failed token clone", false));
	if (!ft_lst_tadd(&list, new))
	{
		msh_ast_token_free(new);
		return (msh_ast_errd(AST_ERROR_ALLOC, ": failed token list", false));
	}
	token->type = TKN_STRING;
	ft_strdel(&token->value.string);
	token->value.list = list;
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
	else if (token && token->type == TKN_WORD)
		err = msh_ast_transform_to_string(token);
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
