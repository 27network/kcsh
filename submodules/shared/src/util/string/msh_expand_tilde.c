/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expand_tilde.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:03:17 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/05 21:03:09 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/env.h>
#include <msh/util.h>

static char	*msh_current_home(t_minishell *msh)
{
	char	*home;

	home = msh_env_value(msh, "HOME");
	if (!home || !*home)
		return ("/tmp");
	return (home);
}

static char	*msh_find_user_home(t_minishell *msh, const char *str,
				size_t *repl_len)
{
	static char		buffer[1024] = {0};
	struct passwd	pwd;
	char			*username;

	username = ft_strndup(str, ft_strcspn(str, "/"));
	if (!username)
		return (NULL);
	pwd = msh_getpwnam(msh, username);
	if (!pwd.pw_name)
		return (NULL);
	ft_bzero(buffer, sizeof(buffer));
	ft_strlcat(buffer, pwd.pw_dir, sizeof(buffer));
	msh_passwd_free(&pwd);
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
		return (str);
	if (str[1] == '/' || !str[1])
		home = msh_current_home(msh, &repl_len);
	else
		home = msh_find_user_home(msh, str + 1, &repl_len);
	if (!home)
		return (ft_strdup(str));
	h_len = ft_strlen(home);
	if (home[len - 1] == '/')
		len--;
	e_len = ft_strlen(src) - 1 + len;
	if (!e_len)
		return (NULL);
	expanded = ft_strnew(e_len);
	if (!expanded)
		return (NULL);
	ft_strlcat(expanded, home, e_len);
	ft_strlcat(expanded, src + 1, e_len);
	return (expanded);
}
