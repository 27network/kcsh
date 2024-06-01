/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_history_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:08:39 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/01 19:33:24 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/cli/history.h>
#include <readline/readline.h>
#include <stdlib.h>

void	msh_history_free(void)
{
	HIST_ENTRY	***ptr;
	HIST_ENTRY	**history;

	rl_clear_history();
	ptr = msh_history_raw();
	if (!ptr || !*ptr)
		return ;
	history = *ptr;
	free(history);
}
