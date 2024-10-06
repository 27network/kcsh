/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:15:48 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/04 03:53:49 by kiroussa         ###   ########.fr       */
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

t_ast_error	msh_ast_build(t_minishell *msh, t_list *tokens,
				t_ast_node **result);
t_ast_error	msh_ast_build_root(t_minishell *msh, t_list *tokens,
				t_ast_node **result);

t_ast_error	msh_ast_node_group(t_minishell *msh, t_list *tokens,
				t_ast_node **result);
t_ast_error	msh_ast_node_command(t_minishell *msh, t_list *tokens,
				t_ast_node **result);
t_ast_error	msh_ast_node_sep(t_minishell *msh, t_list *tokens, t_list *sep,
				t_ast_node **result);

t_ast_error	msh_ast_node_new(t_ast_node **result, t_ast_node_type type);
t_ast_error	msh_ast_node_new_filled(t_ast_node **result, t_ast_node_type type,
				t_ast_node *left, t_ast_node *right);
t_ast_error	msh_ast_node_new_child(t_ast_node **result, t_ast_node_type type,
				t_ast_node *parent);

void		msh_ast_node_free(t_ast_node *node);
void		msh_ast_node_print(t_minishell *msh, t_ast_node *node);
const char	*msh_ast_node_strtype(t_ast_node_type type);

# endif // __MSH_AST_BUILDER_H__
#endif // BUILDER_H
