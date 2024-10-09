/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:17:52 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/09 02:08:12 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# undef LEXER_H
# ifndef __MSH_AST_LEXER_H__
#  define __MSH_AST_LEXER_H__

#  include <ft/data/list.h>
#  include <msh/ast/error.h>
#  include <msh/ast/lexer/kinds.h>
#  include <msh/ast/lexer/tokens.h>
#  include <msh/ast/lexer/types.h>
#  include <msh/minishell.h>

#  define SEP_CHARS " \t\n"
#  define DELIM_CHARS " \t\n{}()[]*?;|&<>`\"&'\\$"
#  define DELIM_CHARS_HEREDOC " \t\n();|&<>`\"'\\"

typedef struct s_ast_lexer
{
	int					id;
	const char			*input;
	t_minishell			*msh;
	struct s_ast_lexer	*parent;
	size_t				cursor;
	const char			*delim;
	bool				found_matching;
	t_list				*tokens;
	bool				allow_escape;
	bool				allow_subst;
	const char			*ifs;
	bool				discrim_mode;
}	t_ast_lexer;

t_ast_lexer	msh_ast_lexer_root(t_minishell *msh, const char *input);
t_ast_lexer	msh_ast_lexer_sub(t_ast_lexer *parent, const char *match);

t_ast_error	msh_ast_token_new(t_ast_token_type type, t_ast_token **tknret);
void		msh_ast_token_free(t_ast_token *token);
t_ast_token	*msh_ast_token_clone(t_ast_token *token);
size_t		msh_ast_token_count(t_list *tokens, t_ast_token_type type);
size_t		msh_ast_token_rcount(t_list *tokens, t_ast_token_type type);

void		msh_ast_token_trace(t_ast_lexer *lexer, t_ast_token_type type,
				int state);
t_ast_error	msh_ast_tokenize(t_ast_lexer *state);
void		msh_ast_tokenize_post(t_ast_lexer *state, t_ast_token *token,
				t_ast_error *err);

void		msh_ast_token_print(t_minishell *msh, t_ast_token *token);
bool		msh_ast_lexer_is_delim(t_ast_lexer *state, const char c);
bool		msh_ast_lexer_check_delim(t_ast_lexer *state, const char c);
void		msh_ast_lexer_debug(t_ast_lexer *lexer, const char *format, ...);

#  define TRACE msh_ast_token_trace

# endif // __MSH_AST_LEXER_H__
#endif // LEXER_H
