/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:15:48 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/17 10:49:09 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDER_H
# define BUILDER_H
# undef BUILDER_H
# ifndef __MSH_AST_BUILDER_H__
#  define __MSH_AST_BUILDER_H__

#  include <msh/ast/error.h>
#  include <msh/ast/types.h>

t_ast_error	msh_ast_build(t_list *tokens, t_ast_node **result);

# endif // __MSH_AST_BUILDER_H__
#endif // BUILDER_H
