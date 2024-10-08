/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_lexer_debug.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 01:13:13 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/11 18:10:33 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/lexer.h>
#define __MSH_LOG_INTERNAL__
#include <msh/log.h>
#include <stdarg.h>

void	msh_ast_lexer_debug(t_ast_lexer *lexer, const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	msh_vlog(lexer->msh, MSG_DEBUG_TOKENIZER, format, args);
	va_end(args);
}
