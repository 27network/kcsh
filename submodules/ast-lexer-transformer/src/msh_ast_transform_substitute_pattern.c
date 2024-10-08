/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_transform_substitute_pattern.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 07:40:33 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/07 03:16:33 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/ast/transformer.h>
#include <msh/env.h>
#include <msh/log.h>

#define LEVEL MSG_DEBUG_EXEC_TRANSFORMER

t_ast_error	msh_ast_transform_substitute_pattern(t_minishell *msh,
				t_list **tokens, __attribute__((unused)) size_t order)
{
	(void)msh;
	(void)tokens;
	return (msh_ast_ok());
}
