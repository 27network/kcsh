/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_contains_shell_metas.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 01:17:57 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/22 01:34:48 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/util.h>

#define META_CHARS " \t\n'\"\\|&;()<>!{}*[?]^$`"

bool	msh_contains_shell_metas(const char *string)
{
	const char	*s;
	char		c;

	s = string;
	while (s && *s)
	{
		c = *s;
		if (ft_strchr(META_CHARS, c))
			return (true);
		if (c == '~' && (s == string || s[-1] == '=' || s[-1] == ':'))
			return (true);
		if (c == '#' && (s == string || s[-1] == '\n'))
			return (true);
		s++;
	}
	return (false);
}
