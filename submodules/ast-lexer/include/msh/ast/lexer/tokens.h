/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 06:52:30 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/27 15:37:34 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H
# undef TOKENS_H
# ifndef __MSH_AST_LEXER_TOKENS_H__
#  define __MSH_AST_LEXER_TOKENS_H__

#  include <ft/data/list.h>
#  include <msh/ast/error.h>
#  include <stdbool.h>

#  ifdef __DUMB_LIBFT_FIX

typedef void				t_list_foreach_fn(void *);

#  endif // __DUMB_LIBFT_FIX

typedef enum e_ast_tkn_type
{
	TKN_SEP = 0,		// An internal separator (space, tab, newline),
						// stripped after sanitization
	TKN_SPACE,			// A space, tab, or newline -- only inside strings
	TKN_KEYWORD,		// if, then, else, elif, fi, ...
	TKN_PIPE,			// |
	TKN_AMP,			// & -- async function
	TKN_DELIM,			// \n, ;, ||, &&
	TKN_REDIR,			// >, >>, <, <<, ...
	TKN_SEMISEMI,		// ;; (end of switch case)
	TKN_GROUP,			// {, }, (, ) -- a collection of tokens
	TKN_STRING,			// collection of words or substituables
	TKN_COMMENT,		// #* -- this is not outputted by the tokenizer
	TKN_WORD,			// singular word
	TKN_BANG,			// singular unquoted !
	TKN_NUMBER,			// singular unquoted number
	TKN_SUBST,			// $var, ${var}, $(...), `...`, $((...))
	TKN_EOF,			// end of file
}	t_ast_token_type;

typedef struct s_ast_token	t_ast_token;

typedef enum e_ast_tkn_redir_state
{
	REDIR_STATE_UNSET = 0,
	REDIR_STATE_FD,
	REDIR_STATE_WORD,
}	t_ast_tkn_redir_state;

typedef struct s_ast_tkn_redir_data
{
	int						left_fd;
	union
	{
		int						right_fd;
		t_ast_token				*right_word;
	};
	t_ast_tkn_redir_state	state;
}	t_ast_tkn_redir_data;

typedef union u_ast_tkn_value
{
	char					c;
	char					*string;
	t_list					*list;
	void					*data;
	t_ast_tkn_redir_data	redir;
}	t_ast_tkn_value;

typedef struct s_ast_token
{
	t_ast_token_type	type;
	int					kind;
	t_ast_tkn_value		value;
}	t_ast_token;

t_ast_error	msh_ast_token_simple(t_ast_token_type type, t_ast_token **tknret,
				size_t *inc, size_t size);
const char	*msh_ast_strtoken(t_ast_token_type type);

# endif // __MSH_AST_LEXER_TOKENS_H__
#endif // TOKENS_H
