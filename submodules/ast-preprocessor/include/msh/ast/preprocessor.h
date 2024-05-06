/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessor.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:45:00 by kiroussa          #+#    #+#             */
/*   Updated: 2024/04/26 20:46:19 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PREPROCESSOR_H
# define PREPROCESSOR_H
# undef PREPROCESSOR_H
# ifndef __MSH_AST_PREPROCESSOR_H__
#  define __MSH_AST_PREPROCESSOR_H__

#  include <ft/data/list.h>
#  include <msh/ast/tokenizer.h>

bool	msh_ast_tkn_verify(t_list *tokens);

# endif // __MSH_AST_PREPROCESSOR_H__
#endif // PREPROCESSOR_H
