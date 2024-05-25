/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:17:52 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/25 11:26:00 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# undef LEXER_H
# ifndef __MSH_AST_LEXER_H__
#  define __MSH_AST_LEXER_H__

#  include <ft/data/list.h>
#  include <msh/ast/error.h>
#  include <msh/ast/tokens.h>
#  include <msh/minishell.h>

#  define SEP_CHARS " \t\n"
#  define QUOTE_CHARS "\"'"
#  define ESCAPE_CHARS "\\"
#  define DELIM_CHARS "\t\n{}()[]*?;|&<>`\"&'\\$"

typedef union u_ast_tkn_value
{
	char	*string;
	t_list	*list;
}	t_ast_tkn_value;

typedef struct s_ast_token
{
	t_ast_tkn_type	type;
	t_ast_tkn_value	value;
}	t_ast_token;

typedef struct s_ast_lexer
{
	const char			*input;
	t_minishell			*msh;
	struct s_ast_lexer	*parent;
	size_t				cursor;
	char				sub_limiter;
	t_list				*tokens;
}	t_ast_lexer;

t_ast_lexer	msh_ast_lexer_root(t_minishell *msh, const char *input);
t_ast_lexer	msh_ast_lexer_sub(t_ast_lexer *parent, char match);

t_ast_error	msh_ast_token_new(t_ast_tkn_type type, t_ast_token **tknret);
void		msh_ast_token_free(t_ast_token *token);

t_ast_error	msh_ast_tokenize(t_ast_lexer *state);

# endif // __MSH_AST_LEXER_H__
#endif // LEXER_H
