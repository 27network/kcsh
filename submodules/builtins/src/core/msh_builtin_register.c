/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin_register.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 23:04:42 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/30 00:09:20 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define __MSH_LOG_INTERNAL__
#include <msh/log.h>
#include <ft/print.h>
#include <msh/builtin.h>
#include <stdbool.h>
#include <stdlib.h>

#if 1 // BUILTIN_REGISTRY_DEBUG
# include <stdarg.h>
# define DBG msh_builtin_debug

static void	msh_builtin_debug(const char *msg, ...)
{
	va_list	ap;

	va_start(ap, msg);
	msh_vlog(NULL, MSG_DEBUG_GENERIC, msg, ap);
	va_end(ap);
}

static void	msh_builtin_check(t_builtin *builtin)
{
	if (!builtin->name)
		DBG("builtin registry: builtin name is NULL\n");
	if (!builtin->func)
		DBG("builtin registry: func for %s is NULL\n", builtin->name);
	if (!builtin->usage || !builtin->help)
		DBG("builtin registry: usage or help for %s is NULL\n",
			builtin->name);
	if (!(builtin->func && builtin->name))
		exit(-2);
}

#else

static void	msh_builtin_check(t_builtin *builtin)
{
	(void)builtin;
}

#endif // BUILTIN_REGISTRY_DEBUG

void	msh_builtin_register(t_builtin builtin)
{
	t_builtin	*builtins;
	size_t		i;

	msh_builtin_check(&builtin);
	builtins = msh_builtin_registry();
	i = 0;
	while (i < BUILTIN_REGISTRY_SIZE)
	{
		if (!builtins[i].name)
		{
			builtins[i] = builtin;
			return ;
		}
		i++;
	}
	ft_dprintf(2, "builtin registry: too many builtins registered, "
		"max is %d\n", BUILTIN_REGISTRY_SIZE);
	exit(-1);
}
