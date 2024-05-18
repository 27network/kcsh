/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_runner_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 03:06:09 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/18 02:15:03 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L // to access SSIZE_MAX
#include <limits.h>
#undef _POSIX_C_SOURCE

#include <errno.h>
#include <fcntl.h>
#include <ft/mem.h>
#include <ft/print.h>
#include <msh/minishell.h>
#include <msh/io.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

static bool	msh_check_binary_file(const char *sample, ssize_t sample_len)
{
	ssize_t			i;
	int				nline;
	unsigned char	c;

	if (sample_len >= 4 && sample[0] == 0x7f && sample[1] == 'E'
		&& sample[2] == 'L' && sample[3] == 'F')
		return (true);
	nline = 1;
	if (sample[0] == '#' && sample[1] == '!')
		nline = 2;
	i = 0;
	while (i < sample_len)
	{
		c = sample[i];
		if (c == '\n' && --nline == 0)
			return (false);
		if (c == '\0')
			return (true);
		i++;
	}
	return (false);
}

static int	msh_runner_check_binary(
	t_minishell *msh,
	const char *file,
	char *string,
	ssize_t nread
) {
	int	ret;

	ret = 0;
	if (nread > 80)
		nread = 80;
	if (msh_check_binary_file(string, nread))
	{
		msh_error(msh, "%s: cannot execute binary file\n", file);
		ret = 126;
	}
	free(string);
	return (ret);
}

static int	msh_runner_check_meta(
	t_minishell *msh,
	const char *file,
	int fd,
	struct stat *st
) {
	size_t	file_size;
	char	*string;
	ssize_t	nread;

	file_size = (size_t) st->st_size;
	if ((off_t) file_size != st->st_size || file_size + 1 < file_size)
	{
		msh_error(msh, "%s: file is too large\n", file);
		return (126);
	}
	else
	{
		if (file_size > SSIZE_MAX)
			file_size = SSIZE_MAX;
		string = ft_calloc(file_size + 1, sizeof(char));
		if (string)
		{
			nread = read(fd, string, file_size);
			if (nread >= 0)
				string[nread] = 0;
			return (msh_runner_check_binary(msh, file, string, nread));
		}
	}
	return (0);
}

static bool	msh_runner_early_exit(t_minishell *msh, const char *file, int fd,
	int *ret)
{
	msh_error(msh, "%s: %s\n", file, strerror(ENOENT));
	*ret = 127;
	close(fd);
	return (false);
}

bool	msh_runner_check(t_minishell *msh, const char *file, int fd, int *ret)
{
	struct stat	st;

	if (!file)
		return (msh_runner_early_exit(msh, file, fd, ret));
	msh->name = file;
	if (fstat(fd, &st) < 0)
	{
		msh_error(msh, "%s: %s\n", file, strerror(errno));
		*ret = 1;
	}
	else if (S_ISDIR(st.st_mode))
	{
		msh_error(msh, "%s: %s\n", file, strerror(EISDIR));
		*ret = 126;
	}
	else if (!S_ISREG(st.st_mode))
	{
		msh_error(msh, "%s: not a regular file\n", file);
		*ret = 126;
	}
	else
		*ret = msh_runner_check_meta(msh, file, fd, &st);
	close(fd);
	return (*ret == 0);
}
