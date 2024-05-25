/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_keyword.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 08:17:41 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/25 08:19:20 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/lexer.h>

t_ast_error	msh_ast_token_keyword(t_ast_lexer *state, t_ast_token **token,
				size_t *inc)
{
	t_ast_error	err;

	err = msh_ast_ok();
	return (err);
}
