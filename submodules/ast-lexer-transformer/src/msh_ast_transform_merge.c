/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_transform_merge.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:22:33 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/07 01:05:21 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/transformer.h>
#include <msh/features.h>
#include <msh/log.h>
#include <msh/util.h>

t_ast_error			msh_ast_transform_try_merge(t_minishell *msh,
						t_list *token, bool *work, size_t order);

void				msh_dump_tokens(t_minishell *msh, t_list *tokens);

t_ast_error	msh_ast_transform_merge_loop(t_minishell *msh,
						t_list *const *tokens, bool *workret, size_t order)
{
	t_list		*current;
	t_ast_error	err;
	bool		work;

	current = *tokens;
	err = msh_ast_ok();
	while (current && err.type == AST_ERROR_NONE)
	{
		work = false;
		msh_log(msh, MSG_DEBUG_EXEC_TRANSFORMER, "merge_loop\n");
		err = msh_ast_transform_try_merge(msh, current, &work, order);
		if (work)
			*workret = true;
		if (err.type != AST_ERROR_NONE)
			break ;
		current = current->next;
	}
	return (err);
}

t_ast_error	msh_ast_transform_merge(
	t_minishell *msh,
	t_list **tokens,
	size_t order
) {
	t_ast_error	err;
	bool		work;

	if (!tokens || !*tokens)
		return (msh_ast_ok());
	err = msh_ast_ok();
	msh_log(msh, MSG_DEBUG_EXEC_TRANSFORMER, "merge (order: %d)\n", (int)order);
	work = true;
	while (err.type == AST_ERROR_NONE && work)
	{
		work = false;
		err = msh_ast_transform_merge_loop(msh, tokens, &work, order);
	}
	return (err);
}
