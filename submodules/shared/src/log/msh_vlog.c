/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_vlog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:10:56 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/06 00:25:07 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string/parse.h>
#include <ft/string.h>
#include <ft/print.h>
#define __MSH_LOG_INTERNAL__
#include <msh/log.h>
#include <msh/util.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

static bool	msh_should_print_type(t_minishell *msh, t_log_type type)
{
	if (!msh)
		return (true);
	if (type == MSG_WARNING || type == MSG_ERROR)
		return (true);
	if (msh->flags.debug_generic)
		return (true);
	if (type == MSG_DEBUG_TOKENIZER)
		return (msh->flags.debug_tokenizer);
	if (type == MSG_DEBUG_EXEC_TRANSFORMER)
		return (msh->flags.debug_transformer);
	if (type == MSG_DEBUG_TOKEN_SANITIZER)
		return (msh->flags.debug_token_sanitizer);
	if (type == MSG_DEBUG_AST_SANITIZER)
		return (msh->flags.debug_ast_sanitizer);
	if (type == MSG_DEBUG_AST_BUILDER)
		return (msh->flags.debug_ast);
	if (type == MSG_DEBUG_EXECUTOR)
		return (msh->flags.debug_executor);
	return (false);
}

static const char	*msh_debug_log_prefix(t_log_type type)
{
	if (type == MSG_DEBUG_GENERIC)
		return ("[DEBUG] ");
	if (type == MSG_DEBUG_TOKENIZER)
		return ("[TKN] ");
	if (type == MSG_DEBUG_TOKEN_SANITIZER)
		return ("[TKN/SANITIZE] ");
	if (type == MSG_DEBUG_AST_SANITIZER)
		return ("[AST/SANITIZE] ");
	if (type == MSG_DEBUG_AST_BUILDER)
		return ("[AST/BUILD] ");
	if (type == MSG_DEBUG_EXECUTOR)
		return ("[EXEC] ");
	if (type == MSG_DEBUG_EXEC_TRANSFORMER)
		return ("[EXEC/TRANSFORM] ");
	return (NULL);
}

static size_t	msh_message_length(t_minishell *msh, t_log_type type,
					const char *msg)
{
	const char	*prefix = msh_debug_log_prefix(type);
	size_t		len;

	len = ft_strlen(msh->name) + 4;
	if (prefix)
		len += ft_strlen(prefix);
	if (type == MSG_DEBUG_EXECUTOR)
		len += 20;
	if (msh && msh->execution_context.show_line)
		len += 5 + 20 + 2;
	if (msg)
		len += ft_strlen(msg);
	return (len);
}

#define TARGET_FD STDERR_FILENO

static void	msh_message_handler(t_minishell *msh, t_log_type type,
	char *msg)
{
	const char		*prefix = msh_debug_log_prefix(type);
	const size_t	len = msh_message_length(msh, type, msg);
	char			*buf;
	char			*tmp;

	buf = ft_calloc(len + 1, sizeof(char));
	if (!buf)
		ft_dprintf(TARGET_FD, "%s: %s\n", msh->name, msg);
	if (msh && (type == MSG_ERROR || msh->execution_context.show_line))
		ft_strlcat(buf, msh->name, len);
	if (msh && (type == MSG_ERROR || msh->execution_context.show_line))
		ft_strlcat(buf, ": ", len);
	ft_strlcat(buf, prefix, len);
	if (buf && msh && msh->execution_context.show_line)
	{
		ft_strlcat(buf, "line ", len);
		tmp = ft_itoa(msh->execution_context.line);
		ft_strlcat(buf, tmp, len);
		free(tmp);
		ft_strlcat(buf, ": ", len);
	}
	ft_strlcat(buf, msg, len);
	if (buf)
		ft_putstr_fd(buf, TARGET_FD);
	free(buf);
}

void	msh_vlog(t_minishell *msh, t_log_type type, const char *format,
			va_list args)
{
	char	*msg;

	if (!msh_should_print_type(msh, type))
		return ;
	msg = NULL;
	if (format && *format)
		ft_vasprintf(&msg, format, args);
	msh_message_handler(msh, type, msg);
	free(msg);
}
