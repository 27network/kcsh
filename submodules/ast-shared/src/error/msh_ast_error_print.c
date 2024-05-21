/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_error_print.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:52:35 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/21 14:44:14 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <msh/ast/error.h>
#include <msh/log.h>

void	msh_ast_error_print(t_minishell *msh, t_ast_error error)
{
	const char	*type_message = msh_ast_strerror(error.type);

	if (error.type == AST_ERROR_NONE)
		return ;
	msh_error(msh, type_message);
	if (error.data)
		msh_ast_error_data(msh, error.type, error.data);
	ft_putchar_fd('\n', STDERR_FILENO);
}
