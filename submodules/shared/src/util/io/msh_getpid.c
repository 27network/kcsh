/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_getpid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 07:42:57 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/30 07:48:10 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <ft/io.h>
#include <ft/string/parse.h>
#include <ft/string.h>
#include <msh/util.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

pid_t	msh_getpid(void)
{
	int		fd;
	pid_t	pid;
	char	*line;

	fd = open("/proc/self/status", O_RDONLY);
	if (fd == -1)
		return (0);
	pid = 0;
	while (pid == 0)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strncmp(line, "Pid:", 4) == 0)
			pid = ft_atoi(line + 4);
		free(line);
	}
	close(fd);
	return (pid);
}
