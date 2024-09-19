/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:18:38 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/19 07:42:32 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SANITIZER_H
# define SANITIZER_H
# undef SANITIZER_H
# ifndef __MSH_AST_SANITIZER_H__
#  define __MSH_AST_SANITIZER_H__

#  include <msh/ast/builder.h>

#  ifndef MSH_SANITIZER_TYPE

//
//       _.---,._,'
//      /' _.--.<
//        /'     `'
//      /' _.---._____
//      \.'   ___, .-'`
//          /'    \\             .
//        /'       `-.          -|-
//       |                       |
//       |                   .-'~~~`-.
//       |                 .'         `.
//       |                 |  R  I  P  |
//       |                 |  kiroussa |
//       |                 |           |
//       |                 | death by  |
//        \              \\| norminette|//
//  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
typedef void		t_i_swear_its_constant;

#   define MSH_SANITIZER_TYPE t_i_swear_its_constant
#  endif

typedef t_ast_error	t_ast_sanitizer_fn(t_minishell *msh,
						MSH_SANITIZER_TYPE **data_ptr);

typedef struct s_ast_sanitizer_info
{
	t_ast_sanitizer_fn	*fn;
	const char			*name;
}	t_ast_sanitizer_info;

t_ast_error	msh_ast_sanitize(t_minishell *msh, t_ast_node **root);
t_ast_error	msh_ast_sanitize_tokens(t_minishell *msh, t_list **tokens);

# endif // __MSH_AST_SANITIZER_H__
#endif // SANITIZER_H
