/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:02:28 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/16 16:03:47 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H
# undef TYPES_H
# ifndef __MSH_AST_TYPES_H__
#  define __MSH_AST_TYPES_H__

#  include <msh/ast/types.h>

typedef struct s_ast_node
{
	t_ast_node	*parent;
	t_ast_node	*left;
	t_ast_node	*right;
	t_ast_token	*token;
}	t_ast_node;

# endif // __MSH_AST_TYPES_H__
#endif // TYPES_H
