/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_strerror.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:49:10 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/17 14:24:28 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/error.h>

/*
 * "<EOF> -> unexpected EOF while looking for matching `<char'
 * echo || | -> syntax error near unexpected token `<token>'
 */

const char	*msh_ast_strerror(t_ast_error_type type)
{
	static const char	*types[] = {
	[AST_ERROR_NONE] = "no error, why was this printed????",
	[AST_ERROR_CANCEL] = "cancelled (non-logging)",
	[AST_ERROR_WARNING] = "warning (non-logging)",
	[AST_ERROR_ALLOC] = "allocation error",
	[AST_ERROR_INPUT] = "input error",
	[AST_ERROR_SYNTAX] = "syntax error",
	[AST_ERROR_UNEXPECTED] = "syntax error near unexpected token",
	[AST_ERROR_UNEXPECTED_EOF] = "unexpected EOF",
	[AST_ERROR_BAD_SUBSTITUTION] = "bad substitution",
	};

	if (type < 0 || type >= _AST_ERROR_COUNT)
		return ("unknown error");
	return (types[type]);
}
