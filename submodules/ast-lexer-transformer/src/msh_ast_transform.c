/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_transform.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:08:36 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/08 19:13:46 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/transformer.h>
#define MSH_SANITIZER_TYPE t_list
#include <msh/ast/sanitizer.h>
#include <msh/log.h>

void		msh_dump_tokens(t_minishell *msh, t_list *tokens);

static t_ast_error	msh_ast_sanitize_tokens_wrapper(t_minishell *msh,
						t_list **tokens, __attribute__((unused)) size_t order)
{
	return (msh_ast_sanitize_tokens(msh, tokens));
}

static t_ast_transformer_info	*msh_ast_transformers(void)
{
	static const t_ast_transformer_info	transformers[] = {
	{.name = "sanitize", .fn = msh_ast_sanitize_tokens_wrapper},
	{.name = "merge", .fn = msh_ast_transform_merge},
	{.name = "substitute_tilde", .fn = msh_ast_transform_substitute_tilde},
	{.name = "substitute_var", .fn = msh_ast_transform_substitute_var},
	{.name = "substitute_pattern", .fn = msh_ast_transform_substitute_pattern},
	{.name = "wordify", .fn = msh_ast_transform_wordify},
	};

	return ((t_ast_transformer_info *) transformers);
}

static void	msh_transformer_log(t_minishell *msh, const char *msg,
				t_ast_error *err, bool stage)
{
	if (stage)
	{
		msh_log(msh, MSG_DEBUG_EXEC_TRANSFORMER, "running transformer '%s'\n",
			msg);
		return ;
	}
	msh_log(msh, MSG_DEBUG_EXEC_TRANSFORMER, "transformer '%s' returned"
		"%s\n", msg, msh_ast_strerror(err->type));
}

t_ast_error	msh_ast_transform_impl(t_minishell *msh, t_list **tokens_ptr,
				bool special)
{
	static const int		order[] = {1, 2, 1, 3, 1, 4, 1, 5, 1};
	size_t					n;
	t_ast_error				err;
	t_ast_transformer_info	transformer;

	if (!tokens_ptr)
		return (msh_ast_errd(AST_ERROR_ALLOC, "invalid token list", false));
	n = 0;
	err = msh_ast_ok();
	while (!err.type && *tokens_ptr && n < sizeof(order) / sizeof(order[0]))
	{
		transformer = msh_ast_transformers()[order[n]];
		msh_transformer_log(msh, transformer.name, NULL, true);
		if (!special || n != 4)
			err = transformer.fn(msh, tokens_ptr, n);
		if (err.type != AST_ERROR_NONE)
			break ;
		msh_dump_tokens(msh, *tokens_ptr);
		transformer = msh_ast_transformers()[0];
		err = transformer.fn(msh, tokens_ptr, 2);
		n++;
	}
	if (err.type != AST_ERROR_NONE)
		msh_transformer_log(msh, transformer.name, &err, false);
	return (err);
}

t_ast_error	msh_ast_transform(t_minishell *msh, t_list **tokens_ptr)
{
	return (msh_ast_transform_impl(msh, tokens_ptr, false));
}
