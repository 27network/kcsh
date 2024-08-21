/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:18:38 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/21 16:48:46 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SANITIZER_H
# define SANITIZER_H
# undef SANITIZER_H
# ifndef __MSH_AST_SANITIZER_H__
#  define __MSH_AST_SANITIZER_H__

#  include <ft/data/list.h>
#  include <msh/ast/lexer.h>

typedef t_ast_error	t_ast_sanitizer_fn(t_minishell *msh, t_list **tokens);

typedef struct s_ast_sanitizer_info
{
	t_ast_sanitizer_fn	*fn;
	const char			*name;
}	t_ast_sanitizer_info;

t_ast_error	msh_ast_sanitize(t_minishell *msh, t_list **tokens);

# endif // __MSH_AST_SANITIZER_H__
#endif // SANITIZER_H
