/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_strerror.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:49:10 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/25 07:42:17 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/error.h>

const char	*msh_ast_strerror(t_ast_error_type type)
{
	static const char	*types[] = {
	[AST_ERROR_NONE] = "no error",
	[AST_ERROR_ALLOC] = "allocation error",
	[AST_ERROR_SYNTAX] = "syntax error",
	[AST_ERROR_UNEXPECTED] = "unexpected token",
	[AST_ERROR_UNEXPECTED_EOF] = "unexpected end of file",
	[AST_ERROR_BAD_SUBSTITUTION] = "bad substitution",
	};

	if (type < 0 || type >= _AST_ERROR_COUNT)
		return ("unknown error");
	return (types[type]);
}
