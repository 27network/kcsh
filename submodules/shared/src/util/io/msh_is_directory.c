/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_is_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 23:57:14 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/06 20:50:51 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>

bool	msh_is_directory(const char *path)
{
	int	fd;

	fd = open(path, O_RDWR);
	if (fd < 0)
		return (errno == EISDIR);
	(void) close(fd);
	return (false);
}
