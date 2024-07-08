/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ansicstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 02:00:40 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/08 18:01:32 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string/parse.h>
#include <ft/string.h>
#include <msh/util.h>

static char	msh_get_escaped_char(char *input)
{
	const char	c = *input;

	if (c == 'c')
	{
		*(input + 1) = '\0';
		return ('\0');
	}
	if (c == 'a')
		return ('\a');
	if (c == 'b')
		return ('\b');
	if (c == 'f')
		return ('\f');
	if (c == 'n')
		return ('\n');
	if (c == 'r')
		return ('\r');
	if (c == 't')
		return ('\t');
	if (c == 'v')
		return ('\v');
	return (c);
}

static int	msh_is_octal_digit(char c)
{
	return (c >= '0' && c <= '7');
}

static int	msh_octal(char **input)
{
	size_t	length;
	int		result;

	*input += 1;
	length = 0;
	result = 0;
	while (msh_is_octal_digit((*input)[length]) && length < 3)
	{
		result = result * 8 + ((*input)[length] - '0');
		length++;
	}
	*input += length;
	return (result);
}

char	*msh_ansicstr(char *input, size_t *retlen)
{
	char	*result;
	char	*tmp;

	if (!input)
		return (NULL);
	result = ft_strnew(ft_strlen(input) * 2);
	if (!result)
		return (NULL);
	tmp = result;
	*retlen = 0;
	while (*input)
	{
		if (*input == '\\')
		{
			input++;
			if (*input == '0')
				*result++ = msh_octal(&input);
			else
				*result++ = msh_get_escaped_char(input++);
		}
		else
			*result++ = *input++;
		*retlen += 1;
	}
	return (tmp);
}
