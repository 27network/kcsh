/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_transform_standardize.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 02:37:49 by kiroussa          #+#    #+#             */
/*   Updated: 2024/08/21 17:44:18 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/transformer.h>

t_ast_error	msh_ast_transform_standardize(t_minishell *msh, t_list **tokens);

static t_ast_error	msh_ast_transform_wrap(t_list *token, t_ast_token *tok)
{
	t_ast_token	*wrapper;
	t_ast_error	err;

	err = msh_ast_token_new(TKN_STRING, &wrapper);
	if (err.type)
		return (err);
	if (!ft_lst_tadd(&wrapper->value.list, tok))
	{
		msh_ast_token_free(wrapper);
		return (msh_ast_errd(AST_ERROR_ALLOC, ": transform_wrap", false));
	}
	token->content = wrapper;
	return (msh_ast_ok());
}

static t_ast_error	msh_ast_transform_try_standardize(t_minishell *msh,
						t_list *token)
{
	static const t_ast_token_type	to_wrap[] = {
		TKN_WORD, //TKN_SUBST
	};
	t_ast_token						*tok;
	size_t							i;
	t_ast_error						err;

	tok = token->content;
	i = 0;
	err = msh_ast_ok();
	while (!err.type && i < sizeof(to_wrap) / sizeof(to_wrap[0]))
	{
		if (tok->type == to_wrap[i])
			err = msh_ast_transform_wrap(token, tok);
		else if (tok->type == TKN_GROUP && tok->value.data)
			err = msh_ast_transform_standardize(msh, &tok->value.list);
		i++;
	}
	return (err);
}

t_ast_error	msh_ast_transform_standardize(
	t_minishell *msh,
	t_list **tokens
) {
	t_list		*current;
	t_ast_error	err;

	if (!tokens || !*tokens)
		return (msh_ast_ok());
	current = *tokens;
	err = msh_ast_ok();
	while (current && !err.type)
	{
		if (current->content)
			err = msh_ast_transform_try_standardize(msh, current);
		current = current->next;
	}
	return (err);
}
