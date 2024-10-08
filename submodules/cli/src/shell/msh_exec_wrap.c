/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_wrap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:01:33 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/30 08:39:36 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/types.h>
#include <msh/exec.h>

int	msh_exec_entry(t_minishell *msh, t_ast_node *node);

bool	msh_exec_wrap(t_minishell *msh, t_ast_node *ast)
{
	return (msh_exec_entry(msh, ast));
}
