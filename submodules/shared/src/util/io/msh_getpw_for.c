/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_getpw_for.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:49:47 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/07 00:23:54 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <ft/io.h>
#include <ft/mem.h>
#include <ft/string/parse.h>
#include <ft/string.h>
#include <msh/util.h>
#include <unistd.h>

static bool	msh_is_pw_correct(struct passwd *pwd, uid_t uid, const char *name)
{
	if ((signed int)uid != -1 && pwd->pw_uid != uid)
		return (false);
	if (name && ft_strcmp(pwd->pw_name, name))
		return (false);
	return (true);
}

static bool	msh_parse_field(struct passwd *pwd, size_t i, char *between)
{
	if (i == 0)
		pwd->pw_name = between;
	else if (i == 1)
		pwd->pw_passwd = between;
	else if (i == 2)
		pwd->pw_uid = ft_atoi(between);
	else if (i == 3)
		pwd->pw_gid = ft_atoi(between);
	else if (i == 4)
		pwd->pw_gecos = between;
	else if (i == 5)
		pwd->pw_dir = between;
	else if (i == 6)
		pwd->pw_shell = between;
	if ((i == 2 || i == 3) && between)
		free((void *)between);
	if (!between)
		return (false);
	return (true);
}

static struct passwd	msh_parse_passwd_line(char *line)
{
	struct passwd	pwd;
	char			*next;
	char			*between;
	size_t			i;

	ft_bzero(&pwd, sizeof(pwd));
	i = 0;
	while (1)
	{
		next = ft_strchr(line, ':');
		if (!next)
			between = ft_strdup_range(line, 0, ft_strlen(line));
		else
			between = ft_strdup_range(line, 0, next - line);
		msh_parse_field(&pwd, i, between);
		i++;
	}
	return (pwd);
}

static bool	msh_getpasswd_file(struct passwd *pwd, uid_t uid, const char *name)
{
	char			*line;
	int				fd;
	bool			found;
	struct passwd	tmp;

	fd = open("/etc/passwd", O_RDONLY);
	if (fd == -1)
		return (false);
	found = false;
	while (!found)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp = msh_parse_passwd_line(line);
		if (msh_is_pw_correct(&tmp, uid, name))
			found = true;
		if (found)
			*pwd = tmp;
		else
			msh_passwd_free(&tmp);
		free(line);
	}
	(void) close(fd);
	return (found);
}

/*
 * struct passwd {
 *    char    *pw_name;       // username
 *    char    *pw_passwd;     // user password
 *    uid_t   pw_uid;         // user ID
 *    gid_t   pw_gid;         // group ID
 *    char    *pw_gecos;      // user information
 *    char    *pw_dir;        // home directory
 *    char    *pw_shell;      // shell program
 * };
 */

struct passwd	msh_getpw_for(t_minishell *msh, uid_t uid, const char *name)
{
	struct passwd	pwd;

	ft_bzero(&pwd, sizeof(pwd));
	if (msh_getpasswd_file(&pwd, uid, name))
		return (pwd);
	ft_bzero(&pwd, sizeof(pwd));
	(void) msh;
	// if (msh_getent_passwd(msh, &pwd, uid, name))
	// 	return (pwd);
	// ft_bzero(&pwd, sizeof(pwd));
	return (pwd);
}
