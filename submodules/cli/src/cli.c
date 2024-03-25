/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:46:03 by maldavid          #+#    #+#             */
/*   Updated: 2024/03/25 18:41:47 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/signal.h>
#include <msh/minishell.h>
#include <msh/io.h>
#include <msh/cli/opt.h>
#include <msh/cli/shell.h>

int	main(int argc, const char *argv[], const char *envp[])
{
	t_minishell	minishell;

	msh_init(&minishell, argc, argv, envp);
	msh_signal_init(&minishell);
	if (argc != 1)
		msh_handle_opts(&minishell, argc, argv);
	msh_shell_loop(&minishell);
	msh_destroy(&minishell);
	return (minishell.exit_code);
}
