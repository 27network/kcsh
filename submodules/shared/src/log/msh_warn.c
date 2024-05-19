/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_warn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:15:22 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/18 20:15:41 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define __MSH_LOG_INTERNALS__
#include <msh/log.h>

void	msh_warn(t_minishell *msh, const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	msh_vlog(msh, MSG_WARNING, format, args);
	va_end(args);
}
