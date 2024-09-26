/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_transform.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:08:36 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/26 00:57:55 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/transformer.h>
#define MSH_SANITIZER_TYPE t_list
#include <msh/ast/sanitizer.h>
#include <msh/log.h>

t_ast_error	msh_ast_transform_merge(t_minishell *msh, t_list **tokens,
				size_t order);
t_ast_error	msh_ast_transform_substitute(t_minishell *msh, t_list **tokens,
				size_t order);
void		msh_dump_tokens(t_minishell *msh, t_list *tokens);

static t_ast_error	msh_ast_sanitize_tokens_wrapper(t_minishell *msh,
						t_list **tokens, __attribute__((unused)) size_t order)
{
	return (msh_ast_sanitize_tokens(msh, tokens));
}

static t_ast_transformer_info	*msh_ast_transformers(void)
{
	static const t_ast_transformer_info	transformers[] = {
	{.name = "merge", .fn = msh_ast_transform_merge},
	{.name = "substitute", .fn = msh_ast_transform_substitute},
	{.name = "sanitize", .fn = msh_ast_sanitize_tokens_wrapper},
	};

	return ((t_ast_transformer_info *)transformers);
}

static int	*msh_ast_transformer_order(size_t *size)
{
	static const int	order[] = {2, 0, 2, 1, 0, 2};
	static const size_t	order_size = sizeof(order) / sizeof(order[0]);

	if (size)
		*size = order_size;
	return ((int *)order);
}

t_ast_error	msh_ast_transform(t_minishell *msh, t_list **tokens_ptr)
{
	static const int		order = {2, 0, 2, 1, 2, 0, 2};
	size_t					n;
	t_ast_error				err;
	t_ast_transformer_info	transformer;

	if (!tokens_ptr)
		return (msh_ast_errd(AST_ERROR_ALLOC, "invalid token list", false));
	n = 0;
	err = msh_ast_ok();
	while (!err.type && *tokens_ptr && n < sizeof(order) / sizeof(order[0]))
	{
		msh_dump_tokens(msh, *tokens_ptr);
		transformer = msh_ast_transformers()[order[n]];
		msh_log(msh, MSG_DEBUG_EXEC_TRANSFORMER, "running transformer '%s'\n",
			transformer.name);
		err = transformer.fn(msh, tokens_ptr, n);
		if (err.type != AST_ERROR_NONE)
			msh_log(msh, MSG_DEBUG_EXEC_TRANSFORMER, "transformer '%s' returned"
				"%s\n", transformer.name, msh_ast_strerror(err.type));
		n++;
	}
	msh_log(msh, MSG_DEBUG_EXEC_TRANSFORMER, "transofmration done\n\n");
	return (err);
}
