/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 22:35:02 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/21 23:58:16 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/builder.h>

bool	msh_ast_create(t_minishell *msh, t_list *tokens, t_ast_node **result)
{
	t_ast_error	err;

	err = msh_ast_build(tokens, result);
	if (err.code != AST_ERROR_OK)
	{
		msh_ast_err_print(err);
		*result = NULL;
		return (false);
	}
	return (true);
}
