/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_canonicalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 05:35:41 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/07 08:29:03 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <msh/util.h>

#define COMP_MAX 2048

static bool	msh_handle_dotslash(const char **inptr)
{
	const char	*in;

	in = *inptr;
	if (in[0] == '.' && (in[1] == '/' || in[1] == 0))
	{
		*inptr = in + 1;
		return (true);
	}
	return (false);
}

static bool	msh_handle_dotdotslash(
	const char **inptr,
	char ***topptr,
	char **outptr,
	int flags
) {
	const char	*in;
	char		**top;
	char		*out;

	in = *inptr;
	top = *topptr;
	out = *outptr;
	if (in[0] == '.' && in[1] == '.' && (in[2] == '/' || in[2] == 0))
	{
		in += 2;
		if (flags & 0x2)
			out = *--top;
		else if (flags & 0x1)
			out = top[-1];
		else
		{
			ft_strcpy(out, "../");
			out += 3;
		}
		*inptr = in;
		*topptr = top;
		*outptr = out;
		return (true);
	}
	return (false);
}

static void	msh_normalize_epilogue(
	const char **inptr,
	char ***topptr,
	char **outptr
) {
	const char	*in;
	char		**top;
	char		*out;

	in = *inptr;
	top = *topptr;
	out = *outptr;
	*top++ = out;
	while (!(*in == 0 || *in == '/'))
		*out++ = *in++;
	if (*in == '/')
		*out++ = '/';
	*inptr = in;
	*topptr = top;
	*outptr = out;
}

static char	*msh_normalize(char *out, const char *in)
{
	const bool	isabs = *in == '/';
	char		*pos[COMP_MAX];
	char		**top;
	char		*head;

	top = pos;
	head = out;
	if (isabs)
		*out++ = '/';
	*top++ = out;
	while (*in != 0)
	{
		while (*in == '/')
			++in;
		if (*in == 0)
			break ;
		if (msh_handle_dotslash(&in) || msh_handle_dotdotslash(&in, &top, &out,
				isabs * 1 + (top - pos > 1) * 2))
			continue ;
		if (top - pos >= COMP_MAX)
			return (NULL);
		msh_normalize_epilogue(&in, &top, &out);
	}
	*out = '\0';
	return (head);
}

char	*msh_canonicalize(const char *path)
{
	char		*ret;
	size_t		size;

	ret = ft_calloc(ft_strlen(path) + 1, sizeof(char));
	if (!ret)
		return (NULL);
	msh_normalize(ret, path);
	size = ft_strlen(ret);
	if (size > 1 && ret[size - 1] == '/')
		ret[size - 1] = '\0';
	return (ret);
}
