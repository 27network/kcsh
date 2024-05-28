/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 20:40:40 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/28 21:20:17 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H
# undef HISTORY_H
# ifndef __MSH_CLI_HISTORY_H__
#  define __MSH_CLI_HISTORY_H__

#  include <readline/history.h>

HIST_ENTRY	***msh_history_raw(void);
void		msh_history_print(void);
void		msh_history_push(const char *line);

# endif // __MSH_CLI_HISTORY_H__
#endif // HISTORY_H
