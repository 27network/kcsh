/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:17:52 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/21 14:48:18 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# undef LEXER_H
# ifndef __MSH_AST_LEXER_H__
#  define __MSH_AST_LEXER_H__

#  include <ft/data/list.h>
#  include <msh/ast/types.h>

t_list	*msh_ast_tokenize(const char *input);

# endif // __MSH_AST_LEXER_H__
#endif // LEXER_H
