/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:54:24 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/13 17:50:54 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H
# undef TYPES_H
# ifndef __MSH_EXEC_TYPES_H__
#  define __MSH_EXEC_TYPES_H__

#  include <msh/minishell.h>

typedef struct s_exec_state
{
	/**
	 * @brief	bon c'est minishell quoi
	 */
	t_minishell	*msh;
	/**
	 * @brief	
	 */
	t_list		*fd_stack;
	/**
	 * @brief	Whether the current command/pipeline is in a piped, basically
	 *			"do we fork or not?"
	 */
	bool		is_in_pipe;
}	t_exec_state;

# endif // __MSH_EXEC_TYPES_H__
#endif // TYPES_H
