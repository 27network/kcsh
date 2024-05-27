/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 21:53:03 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/27 04:38:21 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H
# undef TYPES_H
# ifndef __MSH_AST_LEXER_TYPES_H__
#  define __MSH_AST_LEXER_TYPES_H__

#  include <msh/ast/lexer/tokens.h>
#  include <msh/ast/error.h>

typedef struct s_ast_lexer	t_ast_lexer;

t_ast_error	msh_ast_token_comment(t_ast_lexer *state, t_ast_token **tknret,
				size_t *inc);
t_ast_error	msh_ast_token_delim(t_ast_lexer *state, t_ast_token **tknret,
				size_t *inc);
t_ast_error	msh_ast_token_sep(t_ast_lexer *state, t_ast_token **tknret,
				size_t *inc);
t_ast_error	msh_ast_token_simple(t_ast_token_type type, t_ast_token **tknret,
				size_t *inc, size_t size);
t_ast_error	msh_ast_token_single_quote(t_ast_lexer *state, t_ast_token **tknret,
				size_t *inc);
t_ast_error	msh_ast_token_string(t_ast_lexer *state, t_ast_token **tknret,
				size_t *inc);
t_ast_error	msh_ast_token_substitution(t_ast_lexer *state, t_ast_token **tknret,
				size_t *inc);
t_ast_error	msh_ast_token_word(t_ast_lexer *state, t_ast_token **tknret,
				size_t *inc);

# endif // __MSH_AST_LEXER_TYPES_H__
#endif // TYPES_H
