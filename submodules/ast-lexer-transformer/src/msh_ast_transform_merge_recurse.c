/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_transform_merge_recurse.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:28:39 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/27 15:32:34 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/transformer.h>
#include <msh/log.h>
#include <msh/util.h>

t_ast_error	msh_ast_transform_merge_loop(t_minishell *msh,
				t_list *const *tokens, bool *workret, size_t order);

t_ast_error	msh_ast_transform_merge_recurse(t_minishell *msh,
						t_list **tokens, bool *workret)
{
	t_ast_error	err;

	err = msh_ast_transform_merge_loop(msh, tokens, workret, 0);
	if (err.type == AST_ERROR_NONE)
		err = msh_ast_err(AST_ERROR_CANCEL, false);
	return (err);
}
