/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin_help_page.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:23:52 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/15 23:13:20 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/builtin.h>

void	msh_builtin_help_page(char *name, int fd)
{
	t_builtin	*builtin;

	builtin = msh_builtin_get(name);
	if (!builtin)
	{
		ft_dprintf(fd, "No help available for %s", name);
		return ;
	}
	msh_builtin_print_usage(builtin, fd);
	msh_builtin_print_help(builtin, fd);
}
