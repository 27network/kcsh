/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:18:38 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/17 23:45:19 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SANITIZER_H
# define SANITIZER_H
# undef SANITIZER_H
# ifndef __MSH_AST_SANITIZER_H__
#  define __MSH_AST_SANITIZER_H__

#  include <ft/data/list.h>
#  include <msh/ast/lexer.h>

typedef t_ast_error	t_ast_sanitizer_fn(t_list **tokens);

t_ast_error	msh_ast_sanitize(t_list **tokens);

# endif // __MSH_AST_SANITIZER_H__
#endif // SANITIZER_H
