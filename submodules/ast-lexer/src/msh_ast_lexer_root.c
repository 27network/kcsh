/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_lexer_root.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 07:35:56 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/24 21:39:47 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/lexer.h>
#include <msh/features.h>
#include <stddef.h>

t_ast_lexer	msh_ast_lexer_root(t_minishell *msh, const char *line)
{
	return ((t_ast_lexer){
		.id = 0,
		.msh = msh,
		.input = line,
		.parent = NULL,
		.cursor = 0,
		.delim = 0,
		.found_matching = false,
		.tokens = NULL,
		.allow_escape = FEAT_PARSER_INHIBITORS,
		.ifs = SEP_CHARS,
		.discrim_mode = false
	});
}
