/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:31:58 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/17 14:12:46 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
# undef ERROR_H
# ifndef __MSH_AST_ERROR_H__
#  define __MSH_AST_ERROR_H__

/**
 * @file error.h
 * @brief An error management system for the AST subsystem.
 */

#  include <msh/minishell.h>
#  include <stdbool.h>

/**
 * @brief The type of an AST error.
 *
 * Special types:
 * - AST_ERROR_CANCEL	basically acts as a "return" statement, treated as an
 *						ignored error, cancelling and freeing everything, but
 *						not logging anything.
 * - AST_ERROR_WARNING	acts as a non-logging error. Causes a retry if required,
 *						but without any logging.
 */
typedef enum e_ast_error_type
{
	AST_ERROR_NONE = 0,
	AST_ERROR_CANCEL,
	AST_ERROR_WARNING,
	AST_ERROR_ALLOC,
	AST_ERROR_INPUT,
	AST_ERROR_SYNTAX,
	AST_ERROR_UNEXPECTED,
	AST_ERROR_UNEXPECTED_EOF,
	AST_ERROR_BAD_SUBSTITUTION,
	_AST_ERROR_COUNT,
}	t_ast_error_type;

typedef struct s_ast_error
{
	t_ast_error_type	type;
	void				*data;
	bool				retry;
}	t_ast_error;

/**
 * @brief Conveniance function; returns a new error with type `AST_ERROR_NONE`.
 *
 * @return An AST error with type AST_ERROR_NONE
 */
t_ast_error	msh_ast_ok(void);

/**
 * @brief Conveniance function; returns a new error with type `AST_ERROR_NONE`
 *		  and the given data.
 *
 * @param data The data to associate with the error
 *
 * @return An AST error with type AST_ERROR_NONE and the given data
 */
t_ast_error	msh_ast_okd(void *data);

/**
 * @brief Conveniance function; returns a new error with the given type.
 *
 * @param type The type of the error
 * @param retry Whether the error is recoverable
 *
 * @return An AST error with the given type
 */
t_ast_error	msh_ast_err(t_ast_error_type type, bool retry);

/**
 * @brief Conveniance function; returns a new error with the given type
 *		  and data.
 *
 * @param type The type of the error
 * @param data The data to associate with the error
 * @param retry Whether the error is recoverable
 *
 * @return An AST error with the given type and data
 */
t_ast_error	msh_ast_errd(t_ast_error_type type, void *data, bool retry);

/**
 * @brief Returns the error string associated with the given error type.
 *
 * @param type The type of the error
 *
 * @return The error string
 */
const char	*msh_ast_strerror(t_ast_error_type type);

/**
 * @brief Convenience function; prints the given error type to stderr.
 *
 * @param type The type of the error
 *
 * @note This is equivalent to calling `msh_ast_error_print` with the result of
 *		 `msh_ast_err(type)`.
 */
void		msh_ast_perror(t_minishell *msh, t_ast_error_type type);

/**
 * @brief Prints the given error to stderr.
 *
 * @param msh The minishell instance
 * @param error The error to print
 */
void		msh_ast_error_print(t_minishell *msh, t_ast_error error);

# endif // __MSH_AST_ERROR_H__
#endif // ERROR_H
