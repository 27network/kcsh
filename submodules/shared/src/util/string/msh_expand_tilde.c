/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expand_tilde.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:03:17 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/07 04:18:30 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <msh/env.h>
#include <msh/util.h>

static char	*msh_current_home(t_minishell *msh, size_t *repl_len)
{
	char	*home;

	home = msh_env_value(msh, "HOME");
	if (!home || !*home)
		home = "/tmp";
	*repl_len = 1;
	return (home);
}

static char	*msh_find_user_home(t_minishell *msh, const char *str,
				size_t *repl_len)
{
	static char		buffer[1024] = {0};
	struct passwd	pwd;
	char			username[1024];
	size_t			u_len;

	if (!str || !*str || !ft_strchr(str, '/'))
		return (NULL);
	ft_bzero(username, sizeof(username));
	u_len = ft_strcspn(str, "/");
	if (u_len >= sizeof(username) || u_len == 0)
		return (NULL);
	ft_strlcpy(username, str, u_len + 1);
	pwd = msh_getpwnam(msh, username);
	if (!pwd.pw_name)
	{
		msh_passwd_free(&pwd);
		return (NULL);
	}
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
		return ((char *) str);
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
