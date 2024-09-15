/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:11:31 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/15 19:12:11 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define __MSH_LOG_INTERNAL__
#include <msh/log.h>

void	msh_debug(t_minishell *msh, const char *format, ...)
{
	va_list	args;

	if (format == NULL)
		format = "";
	va_start(args, format);
	msh_vlog(msh, MSG_DEBUG_GENERIC, format, args);
	va_end(args);
}
