/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_transform_pattern_build_str.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 01:28:11 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/09 01:28:39 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <msh/ast/transformer.h>
#include <msh/features.h>

#ifdef FEAT_PATTERN_MATCHING_FULL
# define ESCAPED_CHARS "\\*?" //TODO: add [
#else
# define ESCAPED_CHARS "\\*"
#endif // FEAT_PATTERN_MATCHING_FULL

static size_t	msh_escaped(const char *str, char *buffer)
{
	size_t	len;

	len = 0;
	while (*str)
	{
		if (ft_strchr(ESCAPED_CHARS, *str))
		{
			if (buffer)
				buffer[len] = '\\';
			if (buffer)
				buffer[len + 1] = *str;
			len += 2;
		}
		else
		{
			if (buffer)
				buffer[len] = *str;
			len++;
		}
		str++;
	}
	return (len);
}

static size_t	msh_strtokens(char *buffer,
					t_list *tokens)
{
	size_t		len;
	t_ast_token	*tkn;

	len = 0;
	while (tokens)
	{
		tkn = (t_ast_token *) tokens->content;
		if (tkn->value.data)
		{
			if (tkn->type == TKN_STRING)
				len += msh_strtokens(buffer, tkn->value.list);
			if (tkn->type == TKN_WORD || tkn->type == TKN_SEP)
			{
				if (buffer)
					msh_escaped(tkn->value.string, buffer + len);
				len += msh_escaped(tkn->value.string, NULL);
			}
			if (tkn->type == TKN_SUBST)
				len += ft_strlen(tkn->value.string);
			if (tkn->type == TKN_SUBST)
				ft_strcat(buffer, tkn->value.string);
		}
		tokens = tokens->next;
	}
	return (len);
}

const char	*msh_ast_transform_pattern_build_str(t_list *tokens)
{
	char	*str;
	size_t	len;

	len = msh_strtokens(NULL, tokens);
	if (!len)
		return (NULL);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	msh_strtokens(str, tokens);
	return (str);
}
