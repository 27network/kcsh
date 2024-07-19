/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:02:28 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/19 13:53:31 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H
# undef TYPES_H
# ifndef __MSH_AST_TYPES_H__
#  define __MSH_AST_TYPES_H__

#  include <msh/ast/lexer.h>

typedef enum e_ast_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_DELIM,
	NODE_GROUP,
}	t_ast_node_type;

/**
 * @param args A list of TKN_STRING tokens.
 * @param redirs A list of TKN_REDIR tokens.
 */
typedef struct s_ast_node_command
{
	t_list		*args;
	t_list		*redirs;
}	t_ast_node_command;

typedef struct s_ast_node
{
	struct s_ast_node	*parent;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	t_ast_node_type		type;
	union
	{
		t_ast_delim_type	delim;
		t_ast_node_command	command;
	};
}	t_ast_node;

# endif // __MSH_AST_TYPES_H__
#endif // TYPES_H
