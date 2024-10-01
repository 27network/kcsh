/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expand_tilde.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouchet <ebouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:03:17 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/01 22:27:15 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <msh/env.h>
#include <msh/log.h>
#include <msh/util.h>

#define NAME __FILE_NAME__

static char	*msh_home_env(t_minishell *msh, size_t *repl_len)
{
	static char		buffer[1024] = {0};
	char			*home;

	home = msh_env_value(msh, "HOME");
	if (!home)
		return (NULL);
	ft_bzero(buffer, sizeof(buffer));
	ft_strlcpy(buffer, home, sizeof(buffer));
	*repl_len = ft_strlen(home);
	return (buffer);
}

static char	*msh_current_home(t_minishell *msh, size_t *repl_len)
{
	static char		buffer[1024] = {0};
	int				uid;
	struct passwd	pwd;

	uid = msh_getuid(msh);
	if (uid < 0)
		return (NULL);
	pwd = msh_getpwuid(msh, uid);
	if (!pwd.pw_name)
	{
		msh_passwd_free(&pwd);
		if (msh_env_value(msh, "HOME"))
			return (msh_home_env(msh, repl_len));
		return (NULL);
	}
	ft_bzero(buffer, sizeof(buffer));
	ft_strlcat(buffer, pwd.pw_dir, sizeof(buffer));
	msh_passwd_free(&pwd);
	*repl_len = 1;
	return (buffer);
}

static char	*msh_find_user_home(t_minishell *msh, const char *str,
				size_t *repl_len)
{
	static char		buffer[1024] = {0};
	struct passwd	pwd;
	char			username[1024];
	size_t			u_len;

	if (!str || !*str)
		return (NULL);
	ft_bzero(username, sizeof(username));
	u_len = ft_strcspn(str, "/");
	msh_debug(msh, NAME": home for %s with len %d\n", str, (int)u_len);
	if (u_len >= sizeof(username) || u_len == 0)
		return (NULL);
	ft_strlcpy(username, str, u_len + 1);
	pwd = msh_getpwnam(msh, username);
	msh_debug(msh, NAME": got passwd for '%s': %s %s\n", username,
		pwd.pw_name, pwd.pw_dir);
	if (!pwd.pw_name)
		msh_passwd_free(&pwd);
	if (!pwd.pw_name)
		return (NULL);
	ft_bzero(buffer, sizeof(buffer));
	ft_strlcat(buffer, pwd.pw_dir, sizeof(buffer));
	msh_passwd_free(&pwd);
	*repl_len = ft_strlen(username) + 1;
	return (buffer);
}

char	*msh_expand_tilde(t_minishell *msh, const char *str)
{
	char	*home;
	size_t	h_len;
	size_t	repl_len;
	char	*expanded;
	size_t	e_len;

	if (!str || *str != '~')
		return (ft_strdup(str));
	msh_debug(msh, NAME": requireing tilde expansion: '%s'\n", str);
	if (str[1] == '/' || !str[1])
		home = msh_current_home(msh, &repl_len);
	else
		home = msh_find_user_home(msh, str + 1, &repl_len);
	if (!home)
		return (ft_strdup(str));
	h_len = ft_strlen(home);
	if (home[h_len - 1] == '/')
		h_len--;
	e_len = ft_strlen(str) - repl_len + h_len;
	expanded = ft_calloc(e_len + 1, sizeof(char));
	if (!expanded)
		return (NULL);
	ft_strlcpy(expanded, home, h_len + 1);
	ft_strlcat(expanded, str + repl_len, e_len + 1);
	return (expanded);
}
