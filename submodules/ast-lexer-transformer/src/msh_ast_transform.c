/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_transform.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:08:36 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/13 18:56:30 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/transform.h>

t_ast_error	msh_ast_transform_merge(t_minishell *msh, t_list **tokens);

static t_ast_transformer_info	*msh_ast_transformers(void)
{
	static const t_ast_transformer_info	transformers[] = {
	{.name = "merge", .fn = msh_ast_transform_merge},
	};

	return ((t_ast_transformer_info *)transformers);
}

static int	*msh_ast_transformer_order(size_t *size)
{
	static const int	order[] = {0};
	static const size_t	order_size = sizeof(order) / sizeof(order[0]);

	if (size)
		*size = order_size;
	return ((int *)order);
}

t_ast_error	msh_ast_transform(t_minishell *msh, t_list **tokens_ptr)
{
	const int				*order;
	size_t					size;
	size_t					n;
	t_ast_error				err;
	t_ast_sanitizer_info	sanitizer;

	if (!tokens_ptr)
		return (msh_ast_errd(AST_ERROR_ALLOC, "invalid token list", false));
	n = 0;
	err = msh_ast_ok();
	order = msh_ast_sanitizer_order(&size);
	while (!err.type && *tokens_ptr && n < size)
	{
		sanitizer = msh_ast_sanitizers()[order[n]];
		msh_log(msh, MSG_DEBUG_TRANSFORMER, "running transformer '%s'\n",
			sanitizer.name);
		err = sanitizer.fn(msh, tokens_ptr);
		if (err.type != AST_ERROR_NONE)
			msh_log(msh, MSG_DEBUG_TRANSFORMER, "transformer '%s' returned"
				"%s\n", sanitizer.name, msh_ast_strerror(err.type));
		n++;
	}
	msh_log(msh, MSG_DEBUG_TRANSFORMER, "transofmration done\n\n");
	return (err);
}
