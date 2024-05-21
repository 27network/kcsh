/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_fileno.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:35:42 by kiroussa          #+#    #+#             */
/*   Updated: 2024/02/16 22:25:18 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>

#ifdef __GLIBC__

int	msh_fileno(FILE	*stream)
{
	if (stream == NULL)
	{
		errno = EINVAL;
		return (-1);
	}
	return (stream->_fileno);
}

#elif __MUSL__

int	msh_fileno(FILE	*stream)
{
	if (stream == NULL)
	{
		errno = EINVAL;
		return (-1);
	}
	return (stream->fd);
}

#else
# error "Unsupported libc"
#endif
