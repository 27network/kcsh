/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:10:49 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/19 02:43:16 by kiroussa         ###   ########.fr       */
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
 * @note You **shouldn't** call this, as this value is only used for 
 *		 initialization. You should use the stored value in 
 *		 minishell's instance (msh->interactive).
 *
 * @return True if the shell is running in interactive mode, false otherwise.
 */
bool	msh_is_interactive(void);

/**
 * @brief Provides the number of columns of the running terminal.
 *
 * @param minishell The minishell instance (to access the environment variables).
 *
 * @return the number of columns.
 */
size_t	msh_columns(t_minishell *msh);

/**
 * @brief Compares two strings using the current locale.
 *
 * @param msh The minishell instance.
 * @param s1 The first string.
 * @param s2 The second string.
 *
 * @return An integer less than, equal to, or greater than zero if s1 is found,
 * 		   respectively, to be less than, to match, or be greater than s2.
 *
 * @note This is badly hardcoded stuff but it's the best I can do. I thought
 * 		 about trying to pry the locale instance from glibc, but from what I've
 * 		 seen it's not exposed, or at least not easily so, in the library.
 * @rant 42 subjects let us use useful functions (challenge) [impossible]
 */
int		msh_strcoll(t_minishell *msh, char *s1, char *s2);

/**
 * @brief Gets the current user's effective ID.
 *
 * @param msh The minishell instance.
 *
 * @return the effective user ID.
 */
int		msh_geteuid(t_minishell *msh);

/**
 * @brief Interprets the ANSI escape codes in the given string.
 *
 * @param input The string to interpret.
 * @param retlen A pointer to store the length of the newly interpreted string.
 *
 * @return The interpreted string.
 */
char	*msh_ansicstr(char *input, size_t *retlen);

# endif // __MSH_IO_H__
#endif // IO_H
