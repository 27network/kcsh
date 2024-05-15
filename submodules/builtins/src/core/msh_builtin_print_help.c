/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_print_help.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:23:12 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/15 23:13:30 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/builtin.h>

void	msh_builtin_print_help(t_builtin *builtin, int fd)
{
	size_t	i;
	size_t	last_start;

	if (!builtin)
		return ;
	if (!builtin->help)
		builtin->help = "No help available";
	if (!builtin->usage)
		builtin->usage = "";
	i = 0;
	last_start = 0;
	while (builtin->help[i])
	{
		if (builtin->help[i] == '\n')
		{
			ft_dprintf(fd, "    %.*s\n", (int)(i - last_start),
				builtin->help + last_start);
			last_start = i + 1;
		}
		i++;
	}
	if (last_start < i)
		ft_dprintf(fd, "    %.*s\n", (int)(i - last_start),
			builtin->help + last_start);
}
