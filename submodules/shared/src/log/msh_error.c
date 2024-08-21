/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:38:49 by kiroussa          #+#    #+#             */
/*   Updated: 2024/08/21 17:20:02 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define __MSH_LOG_INTERNAL__
#include <msh/log.h>

void	msh_error(t_minishell *msh, const char *format, ...)
{
	va_list	args;

	if (format == NULL)
		format = "";
	va_start(args, format);
	msh_vlog(msh, MSG_ERROR, format, args);
	va_end(args);
}
