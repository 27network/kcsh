/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 06:52:30 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/25 09:01:09 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H
# undef TOKENS_H
# ifndef __MSH_AST_TOKENS_H__
#  define __MSH_AST_TOKENS_H__

typedef enum e_ast_tkn_type
{
	TKN_KEYWORD,	// if, then, else, elif, fi, ...
	TKN_PIPE,		// |
	TKN_DELIM,		// \n, ;, ||, &&
	TKN_REDIR,		// >, >>, <, <<, ...
	TKN_GROUP,		// (, ), {, } ..., a collection of tokens
	TKN_COMMENT,	// #*
	TKN_STRING,		// collection of words or substituables
	TKN_WORD,		// single word
	TKN_SUBSTI,		// substituables (variable, command substitution, ...)
}	t_ast_tkn_type;

const char	*msh_ast_strtoken(t_ast_tkn_type type);

# endif // __MSH_AST_TOKENS_H__
#endif // TOKENS_H
