/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_syntax_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:00:06 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/24 21:57:26 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <msh/ast/lexer.h>

#define ERROR_MSG " near unexpected token"

const char	*msh_ast_strtoken_simple(t_ast_token *token);
const char	*msh_ast_strtoken_simple_impl(t_ast_token *token,
				const char *paran);

const char	*msh_syntax_error_char(const char c)
{
	char	*msg;
	size_t	len;

	len = ft_strlen(ERROR_MSG) + 3 + 1 + 1;
	msg = ft_calloc(len, sizeof(char));
	if (!msg)
		return (NULL);
	ft_strlcpy(msg, ERROR_MSG, len);
	ft_strlcat(msg, " `", len);
	msg[len - 3] = c;
	ft_strlcat(msg, "'", len);
	return (msg);
}

const char	*msh_syntax_error_impl(t_ast_token *token, const char *paren)
{
	char		*msg;
	size_t		len;
	const char	*preemptive;

	preemptive = msh_ast_strtoken_simple_impl(token, paren);
	if (!preemptive)
		return (ft_strdup(ERROR_MSG));
	len = ft_strlen(ERROR_MSG) + 3 + ft_strlen(preemptive) + 1;
	msg = ft_calloc(len, sizeof(char));
	if (!msg)
		return (NULL);
	ft_strlcpy(msg, ERROR_MSG, len);
	ft_strlcat(msg, " `", len);
	ft_strlcat(msg, preemptive, len);
	ft_strlcat(msg, "'", len);
	return (msg);
}

const char	*msh_syntax_error(t_ast_token *token)
{
	return (msh_syntax_error_impl(token, ")"));
}
