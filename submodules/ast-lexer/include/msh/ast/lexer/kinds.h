/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kinds.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 01:22:00 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/16 14:19:07 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KINDS_H
# define KINDS_H
# undef KINDS_H
# ifndef __MSH_AST_LEXER_KINDS_H__
#  define __MSH_AST_LEXER_KINDS_H__

typedef enum e_ast_keyword
{
	KW_IF = 0,
	KW_THEN,			// End of "if" condition
	KW_ELSE,			// End of previous condition
	KW_ELIF,			// End of previous condition
	KW_FI,				// End of "if"
	KW_DO,				// End of "for, while, until" condition
	KW_DONE,			// End of "while, until, for"
	KW_CASE,
	KW_ESAC,			// End of "case"
	KW_WHILE,
	KW_UNTIL,
	KW_FOR,
	KW_IN,
	KW_BREAK,
	KW_CONTINUE,
	KW_RETURN,
	KW_FUNCTION,
	KW_OPEN_BRACE,
	KW_CLOSE_BRACE,		// End of "function"
	KW_BANG,
	KW_OPEN_BRACKET_BRACKET,
	KW_UNKNOWN,
}	t_ast_keyword_type;

typedef enum e_ast_delim
{
	DELIM_NEWLINE = 0,	// \n
	DELIM_SEMICOLON,	// ;
	DELIM_AND,			// &&
	DELIM_OR,			// ||
}	t_ast_delim_type;

typedef enum e_ast_redir
{
	REDIR_FILE_IN = 0,	// <
	REDIR_FILE_OUT,		// >
	REDIR_FILE_INOUT,	// <>
	REDIR_FILE_APPEND,	// >>
	REDIR_FILE_CLOBBER, // >|
	REDIR_FD_IN,		// <&
	REDIR_FD_OUT,		// >&
	REDIR_HEREDOC,		// <<
	REDIR_HERESTR,		// <<<
}	t_ast_redir_type;

typedef enum e_ast_substitution
{
	SUBST_VAR = 0,		// $var
	SUBST_VAR_RICH,		// ${var}
	SUBST_CMDSUB,		// $(...)
	SUBST_ARITH,		// $((...))
	SUBST_CMDSUB_BQ,	// `...`
	SUBST_ANSI_C,		// $''
	SUBST_LOCALIZED,	// $""
}	t_ast_substitution_type;

typedef enum e_ast_group
{
	GROUP_SUBSHELL = 0,	// (...)
	GROUP_BRACE,		// {...}
}	t_ast_group_type;

# endif // __MSH_AST_LEXER_KINDS_H
#endif // KINDS_H
