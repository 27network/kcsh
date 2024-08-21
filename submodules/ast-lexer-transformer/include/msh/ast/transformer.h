/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:32:59 by kiroussa          #+#    #+#             */
/*   Updated: 2024/08/21 17:33:04 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORMER_H
# define TRANSFORMER_H
# undef TRANSFORMER_H
# ifndef __MSH_AST_TRANSFORMER_H__
#  define __MSH_AST_TRANSFORMER_H__

#  include <msh/ast/types.h>

t_ast_node	*msh_ast_transform(t_ast_node *node);

# endif // __MSH_AST_TRANSFORMER_H__
#endif // TRANSFORMER_H
