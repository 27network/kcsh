/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 01:17:16 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/07 14:45:25 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <msh/util.h>

static char	*msh_quote_short_circuit(char *result)
{
	result[0] = '\\';
	result[1] = '\'';
	result[2] = '\0';
	return (result);
}

static char	*msh_quote_string(char *s, char *r)
{
	char	c;

	while (s && *s)
	{
		c = *s;
		*r++ = c;
		if (c == '\'')
		{
			*r++ = '\\';
			*r++ = '\'';
			*r++ = '\'';
		}
		s++;
	}
	return (r);
}

char	*msh_quote(const char *string)
{
	char	*result;
	char	*r;

	result = ft_calloc(3 + (4 * ft_strlen(string)), sizeof(char));
	if (!result)
		return (NULL);
	r = result;
	if (string[0] == '\'' && string[1] == 0)
		return (msh_quote_short_circuit(result));
	*r++ = '\'';
	r = msh_quote_string((char *) string, r);
	*r++ = '\'';
	*r = '\0';
	return (result);
}
