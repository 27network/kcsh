/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:15:48 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/18 16:33:50 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDER_H
# define BUILDER_H
# undef BUILDER_H
# ifndef __MSH_AST_BUILDER_H__
#  define __MSH_AST_BUILDER_H__

#  include <msh/ast/lexer.h>
#  include <msh/ast/types.h>
#  include <msh/minishell.h>

t_ast_error	msh_ast_build(t_list *tokens, t_ast_node **result);
void		msh_ast_print(t_minishell *msh, t_ast_node *node, int depth);
const char	*msh_ast_strtype(t_ast_node_type type);

# endif // __MSH_AST_BUILDER_H__
#endif // BUILDER_H
