/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 03:36:44 by kiroussa          #+#    #+#             */
/*   Updated: 2024/03/22 17:45:30 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H
# undef TOKENIZER_H
# ifndef __MSH_AST_TOKENIZER_H__
#  define __MSH_AST_TOKENIZER_H__

#  include <ft/data/list.h>
#  include <msh/ast/tokens.h>
#  include <msh/features.h>
#  include <stdbool.h>

#  if FEAT_TKN_ESCAPE == 1
#   define TOKEN_DELIMITERS " =\t\n;|&<>(){}[]$'\"\\"
#  else
#   define TOKEN_DELIMITERS " =\t\n;|&<>(){}[]$'\""
#  endif

#  define _LOWERCASE	"abcdefghijklmnopqrstuvwxyz"
#  define _UPPERCASE	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#  define _DIGITS		"0123456789"
#  define SINGLE_TOKENS "=;&|<>(){}[]\n "

typedef struct s_token
{
	t_token_type		type;
	void				*data;
}	t_token;

t_list	*msh_ast_tokenize(const char *input);
void	msh_ast_tkn_print(t_token *token);
void	msh_ast_tkn_free(t_token *token);

t_token	*msh_ast_tkn_new(t_token_type type, void *data);

#  ifdef TOKENIZER_TYPES

t_token	*msh_ast_tokenize_escape(const char *line, size_t *cursor);
t_token	*msh_ast_tokenize_single(const char *line, size_t *cursor);
t_token	*msh_ast_tokenize_string(const char *line, size_t *cursor);
t_token	*msh_ast_tokenize_variable(const char *line, size_t *cursor);
t_token	*msh_ast_tokenize_word(const char *line, size_t *cursor);

#  endif // TOKENIZER_TYPES

# endif // __MSH_AST_TOKENIZER_H__
#endif // TOKENIZER_H
