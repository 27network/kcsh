/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_build.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:17:03 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/17 10:47:39 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/builder.h>

t_ast_error	msh_ast_build(t_list *tokens, t_ast_node **result)
{
	t_ast_error	err;

	err = msh_ast_ok();
	(void) tokens;
	(void) result;
	return (err);
}
