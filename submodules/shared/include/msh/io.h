/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:10:49 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/17 00:40:44 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H
# undef IO_H
# ifndef __MSH_IO_H__
#  define __MSH_IO_H__

#  include <msh/minishell.h>
#  include <stdio.h>

/**
 * @brief Resolve the path of a file or script
 *
 * @implementation	This function will first try a relative path, then an
 * 					absolute path, and finally search the PATH environment
 * 					variable for the file. If the file is not found, it will
 * 					return NULL.
 *
 * @param msh		The minishell instance
 * @param filename	The name of the file or script
 *
 * @return			The resolved path of the file or script, or `filename` 
 *					if not found. NULL is returned if a memory error happens.
 */
char	*msh_resolve_path(t_minishell *msh, const char *filename);

/**
 * This function checks if the given path is to a directory.
 *
 * @param path The path to check.
 */
bool	msh_is_directory(const char *path);

/**
 * @brief Get the current machine's hostname.
 *
 * @implementation This function reads /etc/hostname to get the hostname,
 * 				   if it fails, it will try and read the $HOSTNAME environment
 * 				   variable. If none work, it will return "localhost".
 * 				   The returned string is malloc'd and is registered to 
 * 				   minishell's free-list, so it will be freed when the 
 * 				   minishell instance gets destroyed.
 *
 * @rant I wish uname wasn't a syscall bruh.
 *
 * @param msh The minishell instance.
 *
 * @return The hostname of the machine.
 */
char	*msh_get_hostname(t_minishell *msh);

/**
 * @brief Get the file descriptor assosiated with the given stream, basically
 * 		  a reimplementation of fileno(3).
 *
 * @implementation This function uses stdlib internals to work, and as such,
 * 				   relies on implementation-specific behavior. It supports
 * 				   glibc and musl, but may not work on other libc's.
 *
 * @param stream The stream to get the file descriptor from.
 *
 * @return The file descriptor of the stream.
 */
int		msh_fileno(FILE	*stream);

/**
 * @note You probably don't need to call this, as this value is stored in 
 *		 minishell's instance (msh->interactive).
 *
 * @return True if the shell is running in interactive mode, false otherwise.
 */
bool	msh_is_interactive(void);

# endif // __MSH_IO_H__
#endif // IO_H
