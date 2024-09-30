/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:54:24 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/30 07:53:12 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H
# undef TYPES_H
# ifndef __MSH_EXEC_TYPES_H__
#  define __MSH_EXEC_TYPES_H__

#  include <msh/minishell.h>
#  include <sys/types.h>
#  include <sys/wait.h>

typedef struct s_exec_state
{
	/**
	 * @brief	The current minishell
	 */
	t_minishell	*msh;
	/**
	 * @brief	A stack of process ids
	 */
	t_list		*pids;
	/**
	 * @brief	The execution depth
	 */
	uint64_t	depth;
}	t_exec_state;

# endif // __MSH_EXEC_TYPES_H__
#endif // TYPES_H
