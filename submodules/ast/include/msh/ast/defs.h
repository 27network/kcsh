/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 23:24:12 by kiroussa          #+#    #+#             */
/*   Updated: 2024/04/26 17:31:44 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H
# undef DEFS_H
# ifndef __MSH_AST_DEFS_H__
#  define __MSH_AST_DEFS_H__

typedef enum s_ast_node_type
{
	AST_PIPELINE_END = 0,		// A pipeline-ending symbol (AND, OR, SEMICOLON)
	AST_PIPELINE_SPLIT,			// A pipe
	AST_ASSIGN,					// A pre-command assignation (NAME=VALUE env)
	AST_REDIR,					// Any type of redirection (<, >>, <<, etc..)
	AST_SUBST,					/* Any type of pre-exec substitution
	empty_line,					// ($VAR, ${EXPR}, *, $((math)), $(cmd) ...)  */
	AST_WORD,					// word word word word word
}	t_ast_node_type;

typedef struct s_ast_node
{
	void				*data;
	t_ast_node_type		type;

	struct s_ast_node	*parent;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

# endif // __MSH_AST_DEFS_H__
#endif // DEFS_H
