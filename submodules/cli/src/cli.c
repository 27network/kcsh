/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:46:03 by kiroussa          #+#    #+#             */
/*   Updated: 2024/02/17 05:18:51 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/minishell.h>
#include <msh/cli/cli.h>
#include <msh/cli/opt.h>
#include <msh/cli/shell.h>
#include <msh/cli/signal.h>

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	minishell;

	msh_init(&minishell, argc, argv, envp);
	msh_signal_init();
	if (argc == 1)
	{
		msh_shell_loop(&minishell);
		return (0);
	}
	else
		return (msh_handle_opts(&minishell));
	return (0);
}
