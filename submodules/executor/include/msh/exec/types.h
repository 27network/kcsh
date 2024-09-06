/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:54:24 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/06 16:55:34 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H
# undef TYPES_H
# ifndef __MSH_EXEC_TYPES_H__
#  define __MSH_EXEC_TYPES_H__

#  include <msh/minishell.h>

typedef struct s_exec_status
{
	int	last_exit_code;
	int	d;
}	t_exec_status;

# endif // __MSH_EXEC_TYPES_H__
#endif // TYPES_H
