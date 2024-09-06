/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 07:24:53 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/06 00:32:07 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# undef EXEC_H
# ifndef __MSH_EXEC_EXEC_H__
#  define __MSH_EXEC_EXEC_H__

/**
 * TODO: @kiroussa: rename this header
 */

#  include <msh/minishell.h>
#  include <msh/ast/types.h>

int	msh_exec_simple(t_minishell *msh, char **line);
int	msh_exec_status(int wait_status);

int	msh_exec_entry(t_minishell *msh, t_ast_node *node);

# endif // __MSH_EXEC_EXEC_H__
#endif // EXEC_H
