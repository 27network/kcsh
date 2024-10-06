/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:02:28 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/04 04:51:13 by kiroussa         ###   ########.fr       */
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
 * @param tokens The initial raw tokens list
 *
 * @param env The inline environment variables, if any (unused)
 * @param args A list of parsed TKN_STRING tokens.
 * @param redirs A list of parsed TKN_REDIR tokens.
 *
 * @param background Whether the command is a background process.
 */
typedef struct s_ast_node_command
{
	t_list		*tokens;

	t_list		*env;
	t_list		*args;
	t_list		*redirs;

	bool		background;
}	t_ast_node_command;

typedef struct s_ast_node_group
{
	t_list		*tokens;

	t_list		*group;

	t_list		*redirs;

	bool		background;
}	t_ast_node_group;

typedef struct s_ast_node
{
	struct s_ast_node	*parent;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	t_list				*tree_tokens;
	t_ast_node_type		type;
	union
	{
		t_ast_delim_type	delim;
		t_ast_node_command	command;
		t_ast_node_group	group;
	};
}	t_ast_node;

# endif // __MSH_AST_TYPES_H__
#endif // TYPES_H
