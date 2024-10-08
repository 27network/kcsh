/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouchet <ebouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:10:49 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/04 05:33:30 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H
# undef UTIL_H
# ifndef __MSH_UTIL_H__
#  define __MSH_UTIL_H__

#  include <msh/minishell.h>
#  include <pwd.h>
#  include <stdint.h>
#  include <stdio.h>
#  include <sys/stat.h>
#  include <sys/types.h>
#  include <unistd.h>

/**
 * @brief Gets the string representation of the given boolean value.
 *
 * @param value The boolean value.
 *
 * @return "true" if the value is `true`, "false" otherwise.
 */
const char		*msh_strbool(bool value);

/**
 * @brief Creates a temporary file.
 *
 * @param prefix The prefix of the temporary file.
 * @param suffix The suffix of the temporary file.
 *
 * @return The path of the temporary file.
 */
const char		*msh_tmpfile(const char *prefix, const char *suffix);

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
char			*msh_resolve_path(t_minishell *msh, const char *filename);

/**
 * @brief Checks if the given path is to a directory.
 *
 * @param path The path to check.
 *
 * @return `true` if the path is to a directory, `false` otherwise.
 */
bool			msh_is_directory(const char *path);

/**
 * @brief Checks if we're running under valgrind.
 *
 * @note This is NOT used to bypass memory checks, but to give a cleaner output
 * during development; this always returns false when not in debug mode.
 *
 * @return `true` if we're running under valgrind, `false` otherwise.
 */
bool			msh_is_valgrind(void);

/**
 * @brief Get the current machine's hostname.
 *
 * @param msh The minishell instance.
 *
 * @return The hostname of the machine.
 */
char			*msh_get_hostname(t_minishell *msh);

/**
 * @brief Get the current machine's host type.
 *
 * @param msh The minishell instance.
 *
 * @return The hosttype of the machine.
 */
char			*msh_get_hosttype(t_minishell *msh);

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
int				msh_fileno(FILE	*stream);

/**
 * @note You **shouldn't** call this, as this value is only used for 
 *		 initialization. You should use the stored value in 
 *		 minishell's instance (msh->interactive).
 *
 * @param msh The minishell instance.
 *
 * @return `true` if the shell is running in interactive mode, `false` otherwise.
 */
bool			msh_is_interactive(t_minishell *msh);

/**
 * @brief Provides the number of lines and columns of the running terminal.
 *
 * @param minishell The minishell instance (to access the fallback environment).
 * @param lines A pointer to store the number of lines.
 * @param columns A pointer to store the number of columns.
 */
void			msh_term_size(t_minishell *msh, size_t *lines, size_t *columns);

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
int				msh_strcoll(t_minishell *msh, const char *s1, const char *s2);

/**
 * @brief Gets the current user's ID.
 *
 * @param msh The minishell instance.
 *
 * @return The user ID.
 */
int				msh_getuid(t_minishell *msh);

/**
 * @brief Gets the current user's effective ID.
 *
 * @param msh The minishell instance.
 *
 * @return The effective user ID.
 */
int				msh_geteuid(t_minishell *msh);

/**
 * @brief Interprets the ANSI escape codes in the given string.
 *
 * @param input The string to interpret.
 * @param retlen A pointer to store the length of the newly interpreted string.
 *
 * @return The interpreted string.
 */
char			*msh_ansicstr(char *input, size_t *retlen);

/**
 * @brief Checks if the given paths are the same file.
 *
 * @param path1 The first path.
 * @param path2 The second path.
 * @param stat1 The stat struct of the first path, or NULL if not required.
 * @param stat2 The stat struct of the second path, or NULL if not required.
 *
 * @return `true` if the paths are the same file, `false` otherwise.
 */
bool			msh_same_file(const char *path1, const char *path2,
					struct stat *stat1, struct stat *stat2);

/**
 * @brief Checks if the given string contains shell metacharacters.
 *
 * @param str The string to check.
 *
 * @return `true` if the string contains shell metacharacters, `false` otherwise.
 */
bool			msh_contains_shell_metas(const char *str);

#  define QUOTING_ANSI_C 0
#  define QUOTING_ESCAPE_QUOTES 1

/**
 * @brief Quotes the given string.
 *
 * @param str The string to quote.
 *
 * @return The quoted string.
 */
char			*msh_quote(const char *str);

/**
 * @brief Performs tilde expansion on the given string.
 *
 * @implementation This function will expand the tilde to the home directory
 *				   of the user. If the tilde is followed by a username, it will
 *				   expand to that user's home directory. If the tilde is not
 *				   followed by a username, it will expand to the home directory
 *				   of the current user.
 *
 * @param msh The minishell instance.
 * @param str The string to expand.
 *
 * @return The expanded string.
 */
char			*msh_expand_tilde(t_minishell *msh, const char *str);

/**
 * @brief Canonicalizes the given path.
 *
 * The new path differs in that:
 * - Multiple `/'s are collapsed to a single `/'.
 * - Leading `./'s and trailing `/.'s are removed.
 * - Trailing `/'s are removed.
 * - Non-leading `../'s and trailing `..'s are handled by removing portions
 *   of the path.
 *
 * @param path The path to canonicalize.
 *
 * @return The canonicalized path.
 */
char			*msh_canonicalize(const char *path);

/**
 * @brief Sets the current working directory to the provided path.
 * 
 * @note This also sets the PWD environment variable and auto-exports it,
 * 		 but does NOT call `chdir`.
 * 
 * @param msh The minishell instance.
 * @param path The working directory path.
 */
void			msh_set_cwd(t_minishell *msh, const char *path);

/**
 * @brief Gets the current process ID.
 *
 * @return The current process ID.
 */
pid_t			msh_getpid(void);

/**
 * @brief Gets the user information from the given user ID.
 *
 * @param msh The minishell instance.
 * @param uid The user ID to get the information from.
 *
 * @return The user information.
 */
struct passwd	msh_getpwuid(t_minishell *msh, uid_t uid);

/**
 * @brief Gets the user information from the given username.
 *
 * @param msh The minishell instance.
 * @param username The username to get the information from.
 *
 * @return The user information.
 */
struct passwd	msh_getpwnam(t_minishell *msh, const char *name);

/**
 * @brief Frees the user information.
 *
 * @param pwd The user information to free.
 */
void			msh_passwd_free(struct passwd *pwd);

/**
* @brief Prints a message indicating that the given command was not found.
*        This will first try to invoke `command-not-found` if
*        it's set, and if not, it will print the message to stderr.
* 
* @param msh The minishell instance.
* @param name The name of the command.
*/
void			msh_command_not_found(t_minishell *msh, const char *name);

# endif // __MSH_UTIL_H__
#endif // UTIL_H
