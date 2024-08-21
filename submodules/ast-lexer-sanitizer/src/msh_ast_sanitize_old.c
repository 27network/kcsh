/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_sanitize_old.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:19:01 by kiroussa          #+#    #+#             */
/*   Updated: 2024/08/17 15:00:31 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/sanitizer.h>
#include <msh/log.h>

t_ast_error	msh_ast_sanitize_check(t_minishell *msh, t_list **tokens);
// t_ast_error	msh_ast_sanitize_merge(t_minishell *msh, t_list **tokens);
// t_ast_error	msh_ast_sanitize_merge_late(t_minishell *msh, t_list **tokens);
// t_ast_error	msh_ast_sanitize_standardize(t_minishell *msh, t_list **tokens);
// t_ast_error	msh_ast_sanitize_wordify(t_minishell *msh, t_list **tokens);

/*
static t_ast_sanitizer_info	*msh_ast_sanitizers(void)
{
	static const t_ast_sanitizer_info	sanitizers[] = {
	{.name = "check", .fn = msh_ast_sanitize_check},
	};

	return ((t_ast_sanitizer_info *)sanitizers);
}

static int	*msh_ast_sanitizer_order(t_minishell *msh, size_t *size)
{
	static const int	order[]
		= {0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0};
	static const int	order_late[]
		= {0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 4, 0, 2, 0, 1, 0};
	static const size_t	order_size
		= sizeof(order) / sizeof(order[0]);
	static const size_t	order_late_size
		= sizeof(order_late) / sizeof(order_late[0]);
	static const bool	late = true;

	(void) msh;
	if (late)
	{
		if (size)
			*size = order_late_size;
		return ((int *)order_late);
	}
	if (size)
		*size = order_size;
	return ((int *)order);
}

t_ast_error	msh_ast_sanitize(t_minishell *msh, t_list **tokens_ptr)
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
	order = msh_ast_sanitizer_order(msh, &size);
	while (!err.type && *tokens_ptr && n++ < size)
	{
		sanitizer = msh_ast_sanitizers()[order[n - 1]];
		msh_log(msh, MSG_DEBUG_AST_SANITIZER, "running sanitizer '%s'\n",
			sanitizer.name);
		err = sanitizer.fn(msh, tokens_ptr);
		if (err.type != AST_ERROR_NONE)
			msh_log(msh, MSG_DEBUG_AST_SANITIZER, "sanitizer '%s' returned"
				"%s\n", sanitizer.name, msh_ast_strerror(err.type));
		if (msh->flags.debug_sanitizer)
			msh_dump_tokens(msh, *tokens_ptr);
	}
	msh_log(msh, MSG_DEBUG_AST_SANITIZER, "sanitization done\n\n");
	return (err);
}
*/
