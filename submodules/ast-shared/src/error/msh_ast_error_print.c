/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_error_print.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:52:35 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/02 01:53:12 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/print.h>
#include <msh/ast/error.h>
#include <msh/log.h>
#include <unistd.h>

static void	msh_ast_error_data(
	__attribute__((unused)) t_minishell *msh,
	__attribute__((unused)) t_ast_error_type type,
	void *data
) {
	ft_putstr_fd(data, STDERR_FILENO);
	if (type == AST_ERROR_UNEXPECTED)
		free(data);
}

void	msh_ast_error_print(t_minishell *msh, t_ast_error error)
{
	const char	*type_message = msh_ast_strerror(error.type);

	if (error.type == AST_ERROR_NONE || error.type == AST_ERROR_CANCEL
		|| error.type == AST_ERROR_WARNING)
		return ;
	ft_putstr_fd(msh->name, STDERR_FILENO);
	if (msh->forked)
		ft_putstr_fd(" (forked)", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (error.data)
		msh_ast_error_data(msh, error.type, error.data);
	else
		ft_putstr_fd(type_message, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}
