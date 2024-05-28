/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 20:40:40 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/29 00:07:15 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H
# undef HISTORY_H
# ifndef __MSH_CLI_HISTORY_H__
#  define __MSH_CLI_HISTORY_H__

#  include <msh/minishell.h>
#  include <stdio.h>
#  include <readline/history.h>

/**
 * @brief Access readline's internal history entry list.
 * 
 * @note This function does dumb memory manipulation and might not work
 * 		 on some systems due to some compilation differences. The functions
 * 		 using it should account for the fact that it might return NULL
 * 		 and act accordingly.
 *
 * @return HIST_ENTRY*** Pointer to the history entry list, or NULL.
 */
HIST_ENTRY	***msh_history_raw(void);
void		msh_history_print(void);

void		msh_history_push(const char *line);

void		msh_history_load(t_minishell *msh);
void		msh_history_save(t_minishell *msh);
int			msh_history_file(t_minishell *msh, int flags);

# endif // __MSH_CLI_HISTORY_H__
#endif // HISTORY_H
