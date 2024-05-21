/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_error_print.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:52:35 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/21 23:44:46 by kiroussa         ###   ########.fr       */
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
	free(data);
}

void	msh_ast_error_print(t_minishell *msh, t_ast_error error)
{
	const char	*type_message = msh_ast_strerror(error.type);

	if (error.type == AST_ERROR_NONE)
		return ;
	msh_error(msh, "%s", type_message);
	if (error.data)
		msh_ast_error_data(msh, error.type, error.data);
	ft_putchar_fd('\n', STDERR_FILENO);
}
