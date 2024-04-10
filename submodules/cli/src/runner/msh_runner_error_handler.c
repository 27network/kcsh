/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_runner_error_handler.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:51:02 by kiroussa          #+#    #+#             */
/*   Updated: 2024/04/10 19:51:52 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <msh/minishell.h>
#include <unistd.h>

void	msh_runner_error_handler(t_minishell *msh, const char *msg)
{
	ft_putstr_fd(STDERR_FILENO, msh->name);
	ft_putstr_fd(STDERR_FILENO, ": line ");
	ft_putstr_fd(STDERR_FILENO, "N/A");
	ft_putstr_fd(STDERR_FILENO, ": ");
	ft_putstr_fd(STDERR_FILENO, msg);
}
