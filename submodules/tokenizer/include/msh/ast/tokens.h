/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 02:05:56 by kiroussa          #+#    #+#             */
/*   Updated: 2024/04/26 17:27:51 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H
# undef TOKENS_H
# ifndef __MSH_AST_TOKENS_H__
#  define __MSH_AST_TOKENS_H__

typedef enum e_token_type
{
	//						// -- Pure tokens -- 
	TKN_WORD = 0,			// any sequence of characters
	TKN_SPACE,				// ' ' or '\t'
	TKN_PIPE,				// '|'
	TKN_SEMICOLON,			// ';'
	TKN_EOF,				// '\0'
	TKN_DOLLAR,				// '$'
	TKN_AMP,				// '&'
	TKN_NEWLINE,			// '\n'
	TKN_REDIR_OUT,			// '>'
	TKN_REDIR_IN,			// '<'
	TKN_LPAREN,				// '('
	TKN_RPAREN,				// ')'
	TKN_LBRACE,				// '{'
	TKN_RBRACE,				// '}'
	TKN_LBRACKET,			// '['
	TKN_RBRACKET,			// ']'
	TKN_ASSIGN,				/* '=' 
	separator,				// -- Compound tokens -- */
	TKN_SUBST,				// substituable token $VAR, ${EXPR}, *[], $((math))
	TKN_ASSIGN_WORD,		// any sequence of characters of the form name=value
	TKN_AND,				// '&&'
	TKN_OR,					// '||'
	TKN_REDIR_APPEND,		// '>>'
	TKN_REDIR_HEREDOC,		/* '<<' or '<<-' 
	separator,				// -- */
	TKN_FD_REF,				// '&[n]' or '&[n]-'
	TKN_REDIR_OUT_CLOBBER,	// '>|'
	TKN_REDIR_HERESTR,		// '<<<'
	TKN_REDIR_BOTH,			// '<>'
	TKN_UNKNOWN,			// any other character
	TKN_COUNT,				//// end of the enum
}	t_token_type;

const char	*msh_ast_tkn_type(t_token_type type);

typedef struct s_tkn_assign_data
{
	char	*key;
	char	*value;
}	t_tkn_assign_data;

# endif // __MSH_AST_TOKENS_H__
#endif // TOKENS_H
