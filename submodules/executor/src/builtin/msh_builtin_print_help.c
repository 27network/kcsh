/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin_print_help.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:23:52 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/15 13:23:20 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <msh/exec/builtin.h>



void	msh_builtin_print_help(char *name, int fd)
{
	const t_builtin	*builtin = msh_builtin_get(name);
	char			**lines;
	size_t			i;

	if (!builtin)
		ft_dprintf(fd, "No help available for %s", name);
	if (!builtin)
		return ;
	msh_print_usage(builtin, fd);
	msh_print_help(builtin, fd);
	// lines = ft_split(usage, '\n');
	// if (lines == NULL && builtin->usage)
	// 	ft_putstr_fd(builtin->usage, fd);
	// if (lines == NULL)
	// 	return ;
	// i = 0;
	// while (lines[i])
	// {
	// 	ft_putstr_fd("    ", fd);
	// 	ft_putendl_fd(lines[i], fd);
	// 	free(lines[i]);
	// 	i++;
	// }
	// free(lines);
}
