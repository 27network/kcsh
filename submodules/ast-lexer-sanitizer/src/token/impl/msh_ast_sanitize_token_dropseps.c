/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_sanitize_token_dropseps.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:25:09 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/18 19:25:29 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/sanitizer.h>
#include <msh/log.h>
#include <msh/util.h>

const char	*msh_syntax_error(t_ast_token *token);

t_ast_error	msh_ast_sanitize_token_dropseps(t_minishell *msh,
						t_list *prev, t_list *current)
{
}
