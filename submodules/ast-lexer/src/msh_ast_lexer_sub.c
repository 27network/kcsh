/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_lexer_sub.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 00:31:55 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/28 13:54:14 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/lexer.h>
#include <stddef.h>

t_ast_lexer	msh_ast_lexer_sub(t_ast_lexer *parent, const char *delim)
{
	t_ast_lexer	lexer;

	lexer.id = parent->id + 1;
	lexer.msh = parent->msh;
	lexer.input = &parent->input[parent->cursor];
	lexer.parent = parent;
	lexer.cursor = 0;
	lexer.delim = delim;
	lexer.found_matching = false;
	lexer.tokens = NULL;
	lexer.ifs = parent->ifs;
	lexer.allow_escape = parent->allow_escape
		&& !msh_ast_lexer_is_delim(&lexer, '\'');
	lexer.discrim_mode = parent->discrim_mode;
	return (lexer);
}
