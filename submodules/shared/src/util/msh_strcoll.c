/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_strcoll.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 23:14:43 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/21 23:39:32 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/env.h>
#include <msh/util.h>

#define UTF8_COLLATED_TABLE "$0123456789aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrR\
sStT\001\002\003\004\005\006\a\b\016\017\020\021\022\023\024\025\026\027\030\
\031\032\033\034\035\036\037\t\n\v\r\f !\"#%&'()*+,-:;<=>?@[\\]^_`{|}~uUvVwW\
xXyYzZ"

static int	msh_get_utf8_collated_index(char *s)
{
	int	i;

	i = 0;
	while (UTF8_COLLATED_TABLE[i])
	{
		if (UTF8_COLLATED_TABLE[i] == *s)
			return (i);
		i++;
	}
	return (i);
}

static int	msh_strcoll_utf8(char *s1, char *s2)
{
	int	i1;
	int	i2;

	i1 = msh_get_utf8_collated_index(s1);
	i2 = msh_get_utf8_collated_index(s2);
	while (*s1 && *s2)
	{
		if (i1 != i2)
			break ;
		i1 = msh_get_utf8_collated_index(s1);
		i2 = msh_get_utf8_collated_index(s2);
		s1++;
		s2++;
	}
	return (i1 - i2);
}

int	msh_strcoll(t_minishell *msh, char *s1, char *s2)
{
	char	*locale;

	locale = msh_env_value(msh, "LC_COLLATE");
	if (!locale || !*locale)
		locale = "C";
	if (*locale == 'C' || !ft_strcmp(locale, "POSIX"))
		return (ft_strcmp(s1, s2));
	return (msh_strcoll_utf8(s1, s2));
}
