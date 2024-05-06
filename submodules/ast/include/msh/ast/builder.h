/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 22:11:56 by kiroussa          #+#    #+#             */
/*   Updated: 2024/04/26 17:34:44 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDER_H
# define BUILDER_H
# undef BUILDER_H
# ifndef __MSH_AST_BUILDER_H__
#  define __MSH_AST_BUILDER_H__

#  include <ft/data/list.h>
#  include <msh/ast/defs.h>

t_ast_node	*msh_ast_node_new(t_ast_node_type type, void *data);
t_ast_node	*msh_ast_build(t_list *tokens);

# endif // __MSH_AST_BUILDER_H__
#endif // BUILDER_H
