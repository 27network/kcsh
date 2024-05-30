/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 20:40:40 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/30 14:54:22 by kiroussa         ###   ########.fr       */
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

/**
 * @brief Print a debug message with the history entry list.
 */
void		msh_history_print(void);

/**
 * @brief Add a line to the history.
 *
 * @param line The line to add.
 *
 * @note This function does some checks to avoid adding NULL or empty lines.
 */
void		msh_history_push(const char *line);

/**
 * @brief Modify the last history entry.
 *
 * @param line The line to modify the last entry with.
 */
void		msh_history_modify_last(const char *line);

/**
 * @brief Open the minishell history file with the provided flags.
 *
 * @param msh The minishell instance.
 * @param flags The flags to open the file with.
 *
 * @return int The file descriptor of the history file, or -1 on error.
 *
 * @note The minishell instance is used to get the HOME environment variable.
 */
int			msh_history_file(t_minishell *msh, int flags);

/**
 * @brief Load the history from the history file.
 *
 * @param msh The minishell instance.
 *
 * @note The history file is found via `msh_history_file`.
 */
void		msh_history_load(t_minishell *msh);

/**
 * @brief Save the history to the history file.
 *
 * @param msh The minishell instance.
 *
 * @note The history file is found via `msh_history_file`.
 */
void		msh_history_save(t_minishell *msh);

# endif // __MSH_CLI_HISTORY_H__
#endif // HISTORY_H
