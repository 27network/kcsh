/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:54:24 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/09 02:12:54 by kiroussa         ###   ########.fr       */
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
	t_minishell	*msh;
	int			last_exit_code;
	t_list		*fd_stack;
}	t_exec_state;

# endif // __MSH_EXEC_TYPES_H__
#endif // TYPES_H
