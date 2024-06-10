/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_opt_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 01:15:04 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/04 11:50:27 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <msh/minishell.h>
#include <msh/features.h>
#include <msh/cli/opt.h>

#define KCSH_SPECIFIC "(kcsh-specific)"

void	msh_print_version(int fd);

void	msh_print_help(t_minishell *msh, int fd)
{
	const char	*argv0;

	argv0 = msh->name;
	ft_dprintf(fd, "Usage:  %s [GNU long option] [option] ...\n", argv0);
	if (FEAT_SCRIPTING)
		ft_dprintf(fd, "        %s [GNU long option] [option] script-file"
			" ...\n", argv0);
	ft_dprintf(fd, "GNU long options:\n");
	ft_dprintf(fd, "        --flags\n");
	ft_dprintf(fd, "        --help\n");
	ft_dprintf(fd, "        --debug\n");
	ft_dprintf(fd, "        --debug-ast\n");
	ft_dprintf(fd, "        --debug-executor\n");
	ft_dprintf(fd, "        --debug-pipelines\n");
	ft_dprintf(fd, "        --debug-sanitizer\n");
	ft_dprintf(fd, "        --debug-tokens\n");
	ft_dprintf(fd, "        --version\n");
	ft_dprintf(fd, "Shell options:\n");
	ft_dprintf(fd, "        -c command         (invocation only)\n");
}

void	msh_opt_help(t_minishell *msh)
{
	const char	*argv0;

	argv0 = msh->name;
	msh_print_version(1);
	msh_print_help(msh, 1);
	if (FEAT_BUILTIN_HELP)
	{
		if (FEAT_BUILTIN_SET)
			ft_printf("Type `%s -c \"help set\"' for more information about "
				"shell options.\n", argv0);
		ft_printf("Type `%s -c help' for more information about shell "
			"builtin commands.\n", argv0);
	}
	ft_printf("\n%s home page: <%s>\n",
		MSH_DEFAULT_NAME, MSH_HOMEPAGE);
	msh_exit(msh, 0);
}
