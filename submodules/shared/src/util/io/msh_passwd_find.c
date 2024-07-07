/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_passwd_find.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 03:38:03 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/07 04:13:37 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/io.h>
#include <ft/mem.h>
#include <ft/string/parse.h>
#include <ft/string.h>
#include <msh/util.h>
#include <unistd.h>

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

static struct passwd	msh_passwd_parse(char *line)
{
	struct passwd	pwd;
	char			*next;
	char			*between;
	size_t			i;
	size_t			len;

	ft_bzero(&pwd, sizeof(pwd));
	i = 0;
	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		line[len - 1] = '\0';
	while (line && line != (char *)1 && *line && i < 7)
	{
		next = ft_strchr(line, ':');
		if (!next)
			between = ft_strdup(line);
		else
			between = ft_strndup(line, next - line);
		if (!msh_parse_field(&pwd, i++, between))
			break ;
		line = next + 1;
	}
	return (pwd);
}

static bool	msh_is_pw_correct(struct passwd *pwd, uid_t uid, const char *name)
{
	if ((signed int)uid != -1 && pwd->pw_uid != uid)
		return (false);
	if (name && ft_strcmp(pwd->pw_name, name))
		return (false);
	return (true);
}

bool	msh_passwd_find(struct passwd *pwd, int fd,
				uid_t uid, const char *name)
{
	char			*line;
	bool			found;
	struct passwd	tmp;

	found = false;
	while (!found)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp = msh_passwd_parse(line);
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
