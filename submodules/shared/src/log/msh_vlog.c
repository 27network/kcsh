/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_vlog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:10:56 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/18 22:39:22 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#define __MSH_LOG_INTERNALS__
#include <msh/log.h>
#include <stdlib.h>
#include <unistd.h>

static void	msh_message_handler(t_minishell *msh, t_log_type type,
	char *msg)
{
	const int	target_fd = STDERR_FILENO;

	if (type != MSG_WARNING || msh->execution_context.show_line)
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

	msg = NULL;
	ft_vasprintf(&msg, format, args);
	if (!msg)
		return ;
	msh_message_handler(msh, type, msg);
	free(msg);
}
