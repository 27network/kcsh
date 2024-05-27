/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_vlog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:10:56 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/27 01:18:45 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#define __MSH_LOG_INTERNALS__
#include <msh/log.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

static bool	msh_should_print_type(t_minishell *msh, t_log_type type)
{
	if (type == MSG_WARNING || type == MSG_ERROR)
		return (true);
	if (type == MSG_DEBUG_AST_TOKENIZER)
		return (msh->flags.debug_tokenizer);
	if (type == MSG_DEBUG_AST_SANITIZER)
		return (msh->flags.debug_sanitizer);
	if (type == MSG_DEBUG_AST_BUILDER)
		return (msh->flags.debug_sanitizer);
	if (type == MSG_DEBUG_EXECUTOR_BUILDER)
		return (msh->flags.debug_pipelines);
	if (type == MSG_DEBUG_EXECUTOR)
		return (msh->flags.debug_executor);
	return (false);
}

static void	msh_message_handler(t_minishell *msh, t_log_type type,
	char *msg)
{
	const int	target_fd = STDERR_FILENO;

	if (type == MSG_ERROR || msh->execution_context.show_line)
	{
		ft_putstr_fd(msh->name, target_fd);
		ft_putstr_fd(": ", target_fd);
	}
	if (msh->execution_context.show_line)
	{
		ft_putstr_fd("line ", target_fd);
		ft_putnbr_fd(msh->execution_context.line, target_fd);
		ft_putstr_fd(": ", target_fd);
	}
	ft_putstr_fd(msg, target_fd);
}

void	msh_vlog(t_minishell *msh, t_log_type type, const char *format,
			va_list args)
{
	char	*msg;

	if (!msh_should_print_type(msh, type))
		return ;
	msg = NULL;
	ft_vasprintf(&msg, format, args);
	if (!msg)
		return ;
	msh_message_handler(msh, type, msg);
	free(msg);
}
