/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_default_error_handler.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:43:04 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/18 03:40:19 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <msh/minishell.h>
#include <unistd.h>

void	msh_default_error_handler(t_minishell *msh, const char *msg)
{
	ft_putstr_fd(msh->name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (msh->execution_context.show_line)
	{
		ft_putstr_fd("line ", STDERR_FILENO);
		ft_putnbr_fd(msh->execution_context.line, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(msg, STDERR_FILENO);
}
