/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_perror.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:50:38 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/26 21:08:37 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/error.h>

void	msh_ast_perror(t_minishell *msh, t_ast_error_type type)
{
	msh_ast_error_print(msh, msh_ast_err(type, false));
}
