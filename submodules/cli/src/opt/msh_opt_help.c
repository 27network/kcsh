/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_opt_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 01:15:04 by kiroussa          #+#    #+#             */
/*   Updated: 2024/03/07 06:23:38 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/minishell.h>
#include <msh/features.h>
#include <msh/cli/opt.h>

void	msh_print_version(int fd);

void	msh_print_help(t_minishell *msh, int fd)
{
	const char	*argv0;

	argv0 = msh->launch_args.argv[0];
	ft_dprintf(fd, "Usage:  %s [GNU long option] [option] ...\n", argv0);
	ft_dprintf(fd, "        %s [GNU long option] [option] script-file ...\n",
		argv0);
	ft_dprintf(fd, "GNU long options:\n");
	ft_dprintf(fd, "        --help\n");
	ft_dprintf(fd, "        --print-ast\n");
	ft_dprintf(fd, "        --print-pipelines\n");
	ft_dprintf(fd, "        --print-tokens\n");
	ft_dprintf(fd, "        --version\n");
	ft_dprintf(fd, "Shell options:\n");
	ft_dprintf(fd, "        -c command         (invocation only)\n");
}

void	msh_opt_help(t_minishell *msh)
{
	const char	*argv0;

	argv0 = msh->launch_args.argv[0];
	msh_print_version(1);
	msh_print_help(msh, 1);
	if (FEAT_BUILTIN_HELP_SET)
		printf("Type `%s -c \"help set\"' for more information about "
			"shell options.\n", argv0);
	if (FEAT_BUILTIN_HELP)
		printf("Type `%s -c help' for more information about shell "
			"builtin commands.\n", argv0);
	printf("\n%s home page: <https://github.com/27network/minishell>\n",
		MSH_DEFAULT_NAME);
	exit(0);
}
