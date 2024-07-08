/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_is_valgrind.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:43:14 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/08 17:47:38 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool	msh_is_valgrind(void)
{
	static bool	is_valgrind = false;
	static bool	is_valgrind_initialized = false;

	if (!is_valgrind_initialized)
	{
		is_valgrind = (getenv("MSH_VALGRIND") != NULL);
		is_valgrind_initialized = true;
		if (is_valgrind)
			printf("[KCSH DEBUG] Running under valgrind, disabling some "
				"well-known **unfixable** leak points\n");
	}
	return (is_valgrind);
}
