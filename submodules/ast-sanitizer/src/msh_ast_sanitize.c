/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_sanitize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:19:01 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/16 18:04:55 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/sanitizer.h>
#include <msh/ast/lexer.h>

t_ast_error	msh_ast_sanitize_check(t_list **tokens);
t_ast_error	msh_ast_sanitize_merge(t_list **tokens);
t_ast_error	msh_ast_sanitize_optimize(t_list **tokens);

t_ast_error	msh_ast_sanitize(t_list **tokens_ptr)
{
	static const t_ast_sanitizer_fn	sanitizers[] = {
		msh_ast_sanitize_check, msh_ast_sanitize_optimize,
		msh_ast_sanitize_check, msh_ast_sanitize_merge,
		msh_ast_sanitize_check, msh_ast_sanitize_optimize,
		msh_ast_sanitize_check,	NULL
	};
	size_t							n;
	t_ast_error						err;

	if (!tokens_ptr)
		return (msh_ast_errd(AST_ERROR_ALLOC, "invalid token list", false));
	n = 0;
	err = msh_ast_ok();
	while (sanitizers[n] && *tokens_ptr)
	{
		err = sanitizers[n](&tokens);
		if (err.type != AST_ERROR_NONE)
			return ;
		n++;
	}
	return (err);
}
