/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:18:38 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/07 18:35:24 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SANITIZER_H
# define SANITIZER_H
# undef SANITIZER_H
# ifndef __MSH_AST_SANITIZER_H__
#  define __MSH_AST_SANITIZER_H__

#  include <ft/data/list.h>
#  include <msh/ast/error.h>

typedef enum e_ast_sanitization_context
{
	SAN_DIRECT,
	SAN_INCREMENTAL,
	SAN_FINAL,
}	t_ast_sanitization_context;

t_ast_error	msh_ast_sanitize_tokens(t_list **tokens,
				t_ast_sanitization_context context);

# endif // __MSH_AST_SANITIZER_H__
#endif // SANITIZER_H
