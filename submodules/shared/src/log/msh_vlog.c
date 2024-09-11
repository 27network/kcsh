/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_vlog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:10:56 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/11 23:09:12 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#define __MSH_LOG_INTERNAL__
#include <msh/log.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

static bool	msh_should_print_type(t_minishell *msh, t_log_type type)
{
	if (!msh)
		return (true);
	if (type == MSG_WARNING || type == MSG_ERROR)
		return (true);
	if (msh->flags.debug_generic)
		return (true);
	if (type == MSG_DEBUG_TOKENIZER)
		return (msh->flags.debug_tokenizer);
	if (type == MSG_DEBUG_EXEC_TRANSFORMER)
		return (msh->flags.debug_transformer);
	if (type == MSG_DEBUG_TOKEN_SANITIZER)
		return (msh->flags.debug_token_sanitizer);
	if (type == MSG_DEBUG_AST_SANITIZER)
		return (msh->flags.debug_ast_sanitizer);
	if (type == MSG_DEBUG_AST_BUILDER)
		return (msh->flags.debug_ast);
	if (type == MSG_DEBUG_EXECUTOR)
		return (msh->flags.debug_executor);
	return (false);
}

static const char	*msh_debug_log_prefix(t_log_type type)
{
	if (type == MSG_DEBUG_GENERIC)
		return ("[DEBUG] ");
	if (type == MSG_DEBUG_TOKENIZER)
		return ("[TKN] ");
	if (type == MSG_DEBUG_TOKEN_SANITIZER)
		return ("[TKN/SANITIZE] ");
	if (type == MSG_DEBUG_AST_SANITIZER)
		return ("[AST/SANITIZE] ");
	if (type == MSG_DEBUG_AST_BUILDER)
		return ("[AST/BUILD] ");
	if (type == MSG_DEBUG_EXECUTOR)
		return ("[EXEC] ");
	if (type == MSG_DEBUG_EXEC_TRANSFORMER)
		return ("[EXEC/TRANSFORM] ");
	return (NULL);
}

static void	msh_message_handler(t_minishell *msh, t_log_type type,
	char *msg)
{
	const int	target_fd = STDOUT_FILENO;
	const char	*prefix = msh_debug_log_prefix(type);

	if (msh && (type == MSG_ERROR || msh->execution_context.show_line))
	{
		ft_putstr_fd(msh->name, target_fd);
		ft_putstr_fd(": ", target_fd);
	}
	if (prefix)
		ft_putstr_fd(prefix, target_fd);
	if (msh && msh->execution_context.show_line)
	{
		ft_putstr_fd("line ", target_fd);
		ft_putnbr_fd(msh->execution_context.line, target_fd);
		ft_putstr_fd(": ", target_fd);
	}
	if (msg)
		ft_putstr_fd(msg, target_fd);
}

void	msh_vlog(t_minishell *msh, t_log_type type, const char *format,
			va_list args)
{
	char	*msg;

	if (!msh_should_print_type(msh, type))
		return ;
	msg = NULL;
	if (format && *format)
		ft_vasprintf(&msg, format, args);
	msh_message_handler(msh, type, msg);
	free(msg);
}
