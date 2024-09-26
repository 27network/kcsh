/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:32:59 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/25 18:59:04 by kiroussa         ###   ########.fr       */
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

typedef struct s_ast_transformer_info
{
	t_ast_transformer_fn	*fn;
	const char				*name;
}	t_ast_transformer_info;

t_ast_error	msh_ast_transform(t_minishell *msh, t_list **tokens);

# endif // __MSH_AST_TRANSFORMER_H__
#endif // TRANSFORMER_H
