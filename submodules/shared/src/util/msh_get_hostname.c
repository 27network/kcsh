/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_get_hostname.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:16:37 by kiroussa          #+#    #+#             */
/*   Updated: 2024/03/22 17:56:03 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <ft/io.h>
#include <ft/string.h>
#include <msh/minishell.h>
#include <stdlib.h>
#include <unistd.h>

char	*msh_get_hostname(t_minishell *msh)
{
	static char	*hostname = NULL;
	int			fd;

	if (!hostname)
	{
		fd = open("/etc/hostname", O_RDONLY);
		if (fd != -1)
		{
			hostname = get_next_line(fd);
			hostname[ft_strlen(hostname) - 1] = '\0';
			close(fd);
		}
		if (!hostname)
			hostname = ft_strdup("localhost");
		ft_lst_tadd(&msh->free_buffer, hostname);
	}
	return (hostname);
}
