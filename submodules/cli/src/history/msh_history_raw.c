/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_history_raw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 20:40:23 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/28 21:33:57 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/cli/history.h>

#include <stdio.h>

HIST_ENTRY	***msh_history_raw(void)
{
	static HIST_ENTRY	***history_ptr = NULL;
	int					*base_ptr;

	if (!history_ptr)
	{
		printf("Getting history from readline\n");
		HIST_ENTRY			**list = history_list();
		printf("Should get something at %p\n", list);
		base_ptr = &history_max_entries;
		printf("Got base at %p\n", base_ptr);
		history_ptr = (HIST_ENTRY ***)base_ptr - (sizeof(int *) + sizeof(int *) + sizeof(HIST_ENTRY **));
		printf("Got history at %p\n", history_ptr);
		printf("Dereferencing history at %p\n", *history_ptr);
	}
	return (history_ptr);
}
