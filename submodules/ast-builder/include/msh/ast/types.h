/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:02:28 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/17 10:48:12 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H
# undef TYPES_H
# ifndef __MSH_AST_TYPES_H__
#  define __MSH_AST_TYPES_H__

#  include <msh/ast/lexer/types.h>

typedef struct s_ast_node
{
	struct s_ast_node	*parent;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	t_ast_token			*token;
}	t_ast_node;

# endif // __MSH_AST_TYPES_H__
#endif // TYPES_H
