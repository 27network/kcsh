/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:19:22 by kiroussa          #+#    #+#             */
/*   Updated: 2024/04/10 19:07:10 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# undef MINISHELL_H
# ifndef __MSH_MINISHELL_H__
#  define __MSH_MINISHELL_H__

/**
 * @file minishell.h
 * @brief Main header file for minishell, holds the main structure and includes
 * 		  many widely-useful function prototypes.
 */

#  include <msh/features.h>
#  include <msh/flags.h>
#  include <ft/data/list.h>
#  include <ft/data/map.h>
#  include <stdbool.h>

#  ifndef MSH_DEFAULT_NAME
#   define MSH_DEFAULT_NAME "minishell"
#  endif // MSH_DEFAULT_NAME

#  ifndef MSH_VERSION
#   define MSH_VERSION "0.0.0-indev"
#  endif // MSH_VERSION

/**
 * @brief Program arguments for minishell. See brief of `t_minishell` 
 *		  for its uses.
 *
 * @param argc Number of arguments.
 * @param argv Arguments as an array of string.
 */
typedef struct s_program_args
{
	int			argc;
	const char	**argv;
}	t_program_args;

/**
 * @brief Error handler function pointer type.
 */
typedef void	t_error_handler(void *msh, const char *msg);

/**
 * @brief Inner structure of minishell.
 *
 * @param binary_name Binary file name, set to argv[0] and never changes.
 * @param name Name of the shell, defaults to argv[0], can be overwritten
 * 			   by the -c and -s flags.
 * @param shell_args Arguments passed to the shell. Note that these are
 *					 not the arguments passed to the shell program itself,
 *					 rather the parsed arguments from -c, -s, and for scripts.
 * @param flags Internal flags for minishell, see `t_msh_flags` in `flags.h`.
 *
 * @param error_handler_fn Function pointer to the error handler, 
 *						   see `t_error_handler`.
 *
 * @param env Environment variables map, see `t_map`.
 * @param exit_code Exit code of the shell.
 * @param interactive Whether the shell is running in interactive mode.
 *
 * @param free_buffer List of pointers to free when the shell is destroyed.
 */
typedef struct s_minishell
{
	const char		*binary_name;
	const char		*name;
	t_program_args	shell_args;
	t_msh_flags		flags;

	t_error_handler	*error_handler;

	t_map			*env;
	int				exit_code;
	bool			interactive;

	t_list			*free_buffer;
}	t_minishell;

/**
 * @brief Initializes minishell with the given program arguments. Note that
 * 		  these arguments aren't stored in `#shell_args`, see the CLI's 
 * 		  option parsing for that.
 *
 * @param msh Minishell instance to initialize.
 * @param argc Number of arguments.
 * @param argv Arguments as an array of string.
 * @param envp Environment variables as an array of string,
 * 			   represented as NAME=VALUE. These are then copied to the
 * 			   environment map `#env`.
 */
void	msh_init(t_minishell *msh, int argc, const char **argv,
			const char **envp);

/**
 * @brief Prints the given message via the error handler.
 *
 * @param msh Minishell instance to print the error with.
 * @param format Format string for the message.
 * @param ... Arguments for the format string.
 */
void	msh_error(t_minishell *msh, const char *format, ...)
		__attribute__((format(printf, 2, 3)));

/**
 * @brief Frees all resources used by minishell.
 *
 * @param msh Minishell instance to destroy.
 *
 * @note Passing a NULL pointer is safe, this function will emit a warning
 *		 and exit with return code -1.
 */
void	msh_destroy(t_minishell *msh);

/**
 * @brief Frees all resources used by minishell and exits with the given
 * 		  exit code. This function should be used instead of `msh_destroy`
 * 		  or `exit` for better callsite management.
 *
 * @param msh Minishell instance to destroy.
 * @param exit_code Exit code to exit with (wrapped to 8 bits, 0-255).
 *
 * @note Passing a NULL pointer is safe, this function will emit a warning
 * 		 and exit with return code -1.
 */
void	msh_exit(t_minishell *msh, int64_t exit_code);

# endif // __MSH_MINISHELL_H__
#endif // MINISHELL_H
