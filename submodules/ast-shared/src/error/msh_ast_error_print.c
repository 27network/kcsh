/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_error_print.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:52:35 by kiroussa          #+#    #+#             */
/*   Updated: 2024/08/21 17:19:45 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/print.h>
#include <msh/ast/error.h>
#include <msh/log.h>
#include <unistd.h>

static char	msh_reverse_match(const char c)
{
	if (c == ')')
		return ('(');
	if (c == '}')
		return ('{');
	if (c == ']')
		return ('[');
	return (c);
}

void	msh_ast_error_free(t_ast_error error)
{
	if (!error.data)
		return ;
	if (error.type == AST_ERROR_SYNTAX)
		free(error.data);
}

static void	msh_ast_error_data(
	__attribute__((unused)) t_minishell *msh,
	const char *type_message,
	t_ast_error	error
) {
	char	c;

	if (error.type != AST_ERROR_UNEXPECTED)
		ft_putstr_fd(type_message, STDERR_FILENO);
	if (error.type == AST_ERROR_UNEXPECTED_EOF)
	{
		c = (char)(unsigned long long) error.data;
		ft_putstr_fd(" while looking for matching `", STDERR_FILENO);
		ft_putchar_fd(msh_reverse_match(c), STDERR_FILENO);
		ft_putchar_fd('\'', STDERR_FILENO);
	}
	else
		ft_putstr_fd(error.data, STDERR_FILENO);
	msh_ast_error_free(error);
}

void	msh_ast_error_print(t_minishell *msh, t_ast_error error)
{
	const char	*type_message = msh_ast_strerror(error.type);

	if (error.type == AST_ERROR_NONE || error.type == AST_ERROR_CANCEL
		|| error.type == AST_ERROR_WARNING)
		return ;
	msh_error(msh, NULL);
	if (error.data)
		msh_ast_error_data(msh, type_message, error);
	else
		ft_putstr_fd(type_message, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}
