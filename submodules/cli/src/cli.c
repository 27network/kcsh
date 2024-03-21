/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:46:03 by kiroussa          #+#    #+#             */
/*   Updated: 2024/03/21 23:46:34 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/minishell.h>
#include <msh/io/system.h>
#include <msh/cli/opt.h>
#include <msh/cli/shell.h>
#include <msh/signal.h>

int	main(int argc, const char *argv[], const char *envp[])
{
	t_minishell	minishell;

	msh_signal_init();
	msh_init(&minishell, argc, argv, envp);
	if (argc != 1)
		msh_handle_opts(&minishell, argc, argv);
	msh_shell_loop(&minishell);
	msh_destroy(&minishell);
	return (minishell.exit_code);
}
