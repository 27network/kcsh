/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_sanitize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 08:03:24 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/10 09:11:29 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MSH_SANITIZER_TYPE t_ast_node
#include <msh/ast/sanitizer.h>

t_ast_error	msh_ast_sanitize(t_minishell *msh, t_ast_node **node)
{
	(void)msh;
	(void)node;
	return (msh_ast_ok());
}
