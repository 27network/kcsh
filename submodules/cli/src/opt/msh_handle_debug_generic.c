/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_handle_debug_generic.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:40:23 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/16 16:31:50 by emfriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/minishell.h>

void	msh_handle_debug_generic(t_minishell *msh, bool generic)
{
	msh->flags.debug_generic = generic;
	msh->flags.debug_tokenizer = true;
	msh->flags.debug_token_sanitizer = true;
	msh->flags.debug_ast = true;
	msh->flags.debug_ast_sanitizer = true;
	msh->flags.debug_transformer = true;
	msh->flags.debug_executor = true;
}
