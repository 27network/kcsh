/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_get_hostname.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:16:37 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/07 02:10:26 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <ft/io.h>
#include <ft/string.h>
#include <msh/env.h>
#include <msh/features.h>
#include <unistd.h>

#if FEAT_SYSCALLS
# include <sys/utsname.h>
#endif // FEAT_SYSCALLS

static char	*msh_read_hostname_file(void)
{
	char	*hostname;
	int		fd;
	size_t	size;

	hostname = NULL;
	fd = open("/etc/hostname", O_RDONLY);
	if (fd != -1)
	{
		hostname = get_next_line(fd);
		if (hostname && *hostname)
		{
			size = ft_strlen(hostname);
			if (hostname[size - 1] == '\n')
				hostname[size - 1] = '\0';
		}
		close(fd);
	}
	return (hostname);
}

#if !FEAT_SYSCALLS
# define HOSTNAME_PROVIDER msh_read_hostname_file
#else
# define HOSTNAME_PROVIDER msh_hostname_via_uname

static char	*msh_hostname_via_uname(void)
{
	char			hostname[256];
	char			*ptr;
	struct utsname	uts;

	ptr = NULL;
	if (uname(&uts) != -1)
	{
		ft_strlcpy(hostname, uts.nodename, sizeof(hostname));
		ptr = ft_strdup(hostname);
	}
	if (!ptr)
		return (msh_read_hostname_file());
	return (ptr);
}

#endif // FEAT_SYSCALLS

char	*msh_get_hostname(t_minishell *msh)
{
	static char	*hostname = NULL;
	static bool	first_run = true;
	int			flags;

	if (!hostname)
		hostname = HOSTNAME_PROVIDER();
	flags = ENV_ALLOC_VALUE;
	if (!hostname)
	{
		hostname = "localhost";
		flags = 0;
	}
	if (first_run)
	{
		msh_env_push(msh, "HOSTNAME", hostname, flags);
		first_run = false;
	}
	return (hostname);
}
