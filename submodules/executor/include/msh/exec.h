/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 07:24:53 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/04 22:48:49 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# undef EXEC_H
# ifndef __MSH_EXEC_H__
#  define __MSH_EXEC_H__

#  include <msh/ast/builder.h>
#  include <msh/exec/types.h>

// S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH
#  define DEFAULT_MODE 0666

int	msh_exec_simple(t_exec_state *state, char **line);
int	msh_exec_status(t_minishell *msh, int wait_status);
int	msh_exec_status_impl(t_minishell *msh, int wait_status, bool in_pipe);

int	msh_exec_entry(t_minishell *msh, t_ast_node *node);

int	msh_exec(t_exec_state *state, t_ast_node *node);
int	msh_exec_command(t_exec_state *state, t_ast_node *node);
int	msh_exec_pipe(t_exec_state *state, t_ast_node *node);
int	msh_exec_delim(t_exec_state *state, t_ast_node *node);
int	msh_exec_group(t_exec_state *state, t_ast_node *node);

# endif // __MSH_EXEC_H__
#endif // EXEC_H
