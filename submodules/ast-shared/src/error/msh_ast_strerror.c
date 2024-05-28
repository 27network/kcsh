/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_strerror.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:49:10 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/28 18:45:25 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/error.h>

const char	*msh_ast_strerror(t_ast_error_type type)
{
	static const char	*types[] = {
	[AST_ERROR_NONE] = "no error, why was this printed????",
	[AST_ERROR_ALLOC] = "allocation error",
	[AST_ERROR_INPUT] = "input error",
	[AST_ERROR_SYNTAX] = "syntax error",
	[AST_ERROR_UNEXPECTED] = "unexpected",
	[AST_ERROR_BAD_SUBSTITUTION] = "bad substitution",
	};

	if (type < 0 || type >= _AST_ERROR_COUNT)
		return ("unknown error");
	return (types[type]);
}
