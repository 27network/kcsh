/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:32:59 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/07 03:09:57 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORMER_H
# define TRANSFORMER_H
# undef TRANSFORMER_H
# ifndef __MSH_AST_TRANSFORMER_H__
#  define __MSH_AST_TRANSFORMER_H__

#  include <msh/ast/types.h>
#  include <msh/ast/error.h>
#  include <msh/minishell.h>
#  include <msh/log.h>

typedef t_ast_error	t_ast_transformer_fn(t_minishell *msh, t_list **tokens,
							size_t n);

t_ast_error	msh_ast_transform_merge(t_minishell *msh, t_list **tokens,
				size_t order);
t_ast_error	msh_ast_transform_substitute_pattern(t_minishell *msh,
				t_list **tokens, size_t order);
t_ast_error	msh_ast_transform_substitute_tilde(t_minishell *msh,
				t_list **tokens, size_t order);
t_ast_error	msh_ast_transform_substitute_var(t_minishell *msh, t_list **tokens,
				size_t order);
t_ast_error	msh_ast_transform_wordify(t_minishell *msh, t_list **tokens,
				size_t order);

typedef struct s_ast_transformer_info
{
	t_ast_transformer_fn	*fn;
	const char				*name;
}	t_ast_transformer_info;

t_ast_error	msh_ast_transform(t_minishell *msh, t_list **tokens);
t_ast_error	msh_ast_transform_impl(t_minishell *msh, t_list **tokens,
				bool special);

# endif // __MSH_AST_TRANSFORMER_H__
#endif // TRANSFORMER_H
