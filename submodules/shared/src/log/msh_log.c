/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_log.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:14:54 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/18 21:53:08 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define __MSH_LOG_INTERNALS__
#include <msh/log.h>

void	msh_log(t_minishell *msh, t_log_type type, const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	msh_vlog(msh, type, format, args);
	va_end(args);
}
