/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin_print_help.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:23:52 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/15 13:58:09 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <msh/exec/builtin.h>

static void	msh_print_usage(t_builtin *builtin, int fd)
{
	ft_dprintf(fd, "%s: %s", builtin->name, builtin->name);
	if (builtin->usage)
		ft_dprintf(fd, " %s", builtin->usage);
	ft_putchar_fd('\n', fd);
}

static void	msh_print_help(t_builtin *builtin, int fd)
{
	char	**lines;
	size_t	i;

	if (!builtin->help)
		builtin->help = "No help available";
	lines = ft_split(builtin->help, '\n');
	if (lines == NULL)
	{
		ft_putendl_fd(builtin->help, fd);
		return ;
	}
	i = 0;
	while (lines[i])
	{
		ft_putstr_fd("    ", fd);
		ft_putendl_fd(lines[i], fd);
		free(lines[i]);
		i++;
	}
	free(lines);
}

void	msh_builtin_print_help(char *name, int fd)
{
	t_builtin	*builtin;

	builtin = msh_builtin_get(name);
	if (!builtin)
	{
		ft_dprintf(fd, "No help available for %s", name);
		return ;
	}
	msh_print_usage(builtin, fd);
	msh_print_help(builtin, fd);
}
