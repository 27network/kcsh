/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:07:05 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/11 23:06:56 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_H
# define LOG_H
# undef LOG_H
# ifndef __MSH_LOG_H__
#  define __MSH_LOG_H__

/**
 * @file log.h
 * @brief Logging system for minishell.
 */

#  include <msh/minishell.h>

#  ifdef __MSH_LOG_INTERNAL__
#   include <stdarg.h>
#  endif // __MSH_LOG_INTERNAL__

/**
 * @brief A message type for logs.
 */
typedef enum e_log_type
{
	MSG_ERROR = 0,
	MSG_WARNING,
	MSG_DEBUG_GENERIC,
	MSG_DEBUG_TOKENIZER,
	MSG_DEBUG_TOKEN_SANITIZER,
	MSG_DEBUG_AST_BUILDER,
	MSG_DEBUG_AST_SANITIZER,
	MSG_DEBUG_EXEC_TRANSFORMER,
	MSG_DEBUG_EXECUTOR,
}	t_log_type;

#  ifdef __MSH_LOG_INTERNAL__
/**
 * @brief Internal implementation of the log function, which takes directly
 * 		  a va_list.
 *
 * @param msh	 Minishell instance.
 * @param type	 Type of the message, see `t_log_type`.
 * @param format Format string for the message.
 * @param args	 Arguments for the format string.
 *
 * @note  This function is not meant to be used directly, use `msh_log`
 *		  or its typed equivalents instead.
 */
void	msh_vlog(t_minishell *msh, t_log_type type, const char *format,
			va_list args);
#  endif // __MSH_LOG_INTERNAL__

/**
 * @brief Prints the given log message.
 *
 * @param msh Minishell instance.
 * @param type Type of the message, see `t_log_type`.
 * @param format Format string for the message.
 * @param ... Arguments for the format string.
 */
void	msh_log(t_minishell *msh, t_log_type type, const char *format, ...)
		__attribute__((format(printf, 3, 4)));

/**
 * @brief Prints the given warning message.
 *
 * @param msh Minishell instance.
 * @param format Format string for the message.
 * @param ... Arguments for the format string.
 */
void	msh_warn(t_minishell *msh, const char *format, ...)
		__attribute__((format(printf, 2, 3)));

/**
 * @brief Prints the given error message.
 *
 * @param msh Minishell instance.
 * @param format Format string for the message.
 * @param ... Arguments for the format string.
 */
void	msh_error(t_minishell *msh, const char *format, ...)
		__attribute__((format(printf, 2, 3)));

# endif // __MSH_LOG_H__
#endif // LOG_H
