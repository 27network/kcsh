/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_opt_version.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:03:09 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/11 23:46:12 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <msh/minishell.h>
#include <msh/cli/opt.h>

void	msh_print_version(int fd)
{
	ft_dprintf(fd, "%s, version %s\n", MSH_DEFAULT_NAME, MSH_VERSION);
}

void	msh_opt_version(t_minishell *msh)
{
	msh_print_version(1);
	ft_printf("Copyright (C) 2024 Seekrs\n");
	ft_printf("License MIT: <https://opensource.org/licenses/MIT>\n\n");
	ft_printf("This is free software; you are free to change and "
		"redistribute it.\n");
	ft_printf("There is NO WARRANTY, to the extent permitted by law.\n");
	msh_exit(msh, 0);
}
