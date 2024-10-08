/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_is_subst_pattern.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 00:32:40 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/07 00:33:03 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/ast/lexer.h>

bool	msh_ast_token_is_subst_pattern(t_ast_token *token)
{
	return (token && token->type == TKN_SUBST && token->kind == SUBST_PATTERN);
}
