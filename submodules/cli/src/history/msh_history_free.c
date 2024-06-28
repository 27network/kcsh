/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_history_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:08:39 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/28 22:17:27 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/features.h>
#if !FEAT_NO_READLINE

# include <msh/cli/history.h>
# include <stdlib.h>

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

#else

/**
 * This function is a no-op when using libshakespeare as the lib's destructor
 * will take care of freeing the history.
 */
void	msh_history_free(void)
{
}

#endif // !FEAT_NO_READLINE
