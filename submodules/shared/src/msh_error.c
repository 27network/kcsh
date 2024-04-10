/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:38:49 by kiroussa          #+#    #+#             */
/*   Updated: 2024/04/10 19:07:55 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <msh/minishell.h>
#include <stdarg.h>
#include <stdlib.h>

/**
 * @brief Default error handler for minishell, prints the message to stderr.
 *
 * @param msh Minishell instance to print the error with.
 * @param msg Message to print.
 */
void	msh_default_error_handler(void *msh, const char *msg);

void	msh_error(t_minishell *msh, const char *format, ...)
{
	va_list	args;
	char	*msg;

	if (!msh->error_handler)
		msh->error_handler = &msh_default_error_handler;
	va_start(args, format);
	ft_vasprintf(&msg, format, args);
	va_end(args);
	msh->error_handler(msh, msg);
	free(msg);
}
