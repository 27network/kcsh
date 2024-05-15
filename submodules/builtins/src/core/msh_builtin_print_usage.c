/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_print_usage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:22:44 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/15 23:13:40 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/builtin.h>

void	msh_builtin_print_usage(t_builtin *builtin, int fd)
{
	if (!builtin)
		return ;
	ft_dprintf(fd, "%s: ", builtin->name);
	if (builtin->usage)
		ft_putendl_fd(builtin->usage, fd);
	else
		ft_putendl_fd(builtin->name, fd);
}
