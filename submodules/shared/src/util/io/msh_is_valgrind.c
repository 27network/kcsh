/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_is_valgrind.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:43:14 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/29 17:47:54 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool	msh_is_valgrind(void)
{
	static bool	is_valgrind = false;
	static bool	is_valgrind_initialized = false;
	char		*env;

	if (!is_valgrind_initialized)
	{
		env = getenv("MSH_VALGRIND");
		if (env)
			is_valgrind = env[0] == '1';
		is_valgrind_initialized = true;
		if (is_valgrind)
		{
			printf("[KCSH DEBUG] Running under valgrind, disabling some "
				"**unfixable** leak points for dev experience\n");
			printf("[KCSH DEBUG] To disable this, add `NO_VG=0` to "
				"your `make valgrind` command\n");
		}
	}
	return (is_valgrind);
}
