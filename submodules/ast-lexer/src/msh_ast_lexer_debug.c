/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_lexer_debug.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 01:13:13 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/30 00:05:06 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define __MSH_LOG_INTERNAL__
#include <msh/log.h>
#include <stdarg.h>

void	msh_ast_lexer_debug(t_minishell *msh, const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	msh_vlog(msh, MSG_DEBUG_AST_TOKENIZER, format, args);
	va_end(args);
}
