/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_build.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 22:11:39 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/14 17:59:01 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/builder.h>
#include <stddef.h>

t_ast_node	*msh_ast_build(t_list *tokens)
{
	t_ast_node	*root;

	(void) tokens;
	root = NULL;
	return (root);
}
