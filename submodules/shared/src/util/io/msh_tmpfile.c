/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_tmpfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:00:30 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/30 14:45:17 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <ft/mem.h>
#include <ft/string.h>
#include <msh/log.h>
#include <msh/util.h>
#include <stdlib.h>
#include <unistd.h>

#define TMP_FILE_RANDOM_LEN 32
#define TMP_FILE_LOCATION "/tmp/"
#define TMP_FILE_MAX_THRESHOLD 1024

static int	msh_rand(void)
{
	static uint64_t	next = 1;

	next = next * 1103515243 + 12345;
	return ((unsigned int)(next / 65536) % 32768);
}

static char	*msh_random_name(void)
{
	static char	name[TMP_FILE_RANDOM_LEN + 1];
	static char	chars[]
		= "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	size_t		i;

	i = 0;
	while (i < TMP_FILE_RANDOM_LEN)
	{
		name[i] = chars[msh_rand() % 62];
		i++;
	}
	name[TMP_FILE_RANDOM_LEN] = '\0';
	return (&name[0]);
}

static bool	msh_can_create_file(const char *path)
{
	int	fd;

	fd = open(path, O_CREAT | O_EXCL | O_RDWR, 0600);
	if (fd == -1)
		return (false);
	close(fd);
	return (true);
}

static char	*msh_beg_for_path(char *path, size_t threshold)
{
	if (threshold >= TMP_FILE_MAX_THRESHOLD)
	{
		free(path);
		return (NULL);
	}
	return (path);
}

const char	*msh_tmpfile(const char *prefix, const char *suffix)
{
	char	*name;
	size_t	len;
	size_t	threshold;

	if (!suffix)
		suffix = ".tmp";
	len = ft_strlen(TMP_FILE_LOCATION) + ft_strlen(prefix) + TMP_FILE_RANDOM_LEN
		+ 10 + ft_strlen(suffix);
	name = ft_calloc(1, len + 1);
	if (!name)
		return (NULL);
	threshold = 0;
	while (threshold < TMP_FILE_MAX_THRESHOLD)
	{
		ft_bzero(name, len + 1);
		ft_strlcpy(name, TMP_FILE_LOCATION, len);
		if (prefix)
			ft_strlcat(name, prefix, len);
		ft_strlcat(name, msh_random_name(), len);
		ft_strlcat(name, suffix, len);
		if (access(name, F_OK) == -1 && msh_can_create_file(name))
			break ;
		threshold++;
	}
	return (msh_beg_for_path(name, threshold));
}
