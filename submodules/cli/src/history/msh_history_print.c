/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_history_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 21:01:25 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/28 20:18:33 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/features.h>
#include <msh/cli/history.h>

#if FEAT_NO_READLINE
# include <ft/print.h>

void	msh_history_print(void)
{
	ft_dprintf(2, "shakespeare history printing not implemented\n");
}

#else

void	msh_history_print(void)
{
	HIST_ENTRY	***ptr;
	HIST_ENTRY	**history;
	int			i;

	ptr = msh_history_raw();
	if (!ptr || !*ptr)
		return ;
	history = *ptr;
	i = 0;
	while (history[i])
	{
		printf("ENTRY { line=\"%s\", timestamp=\"%s\", data=\"%p\" }\n",
			history[i]->line, history[i]->timestamp, history[i]->data);
		i++;
	}
}

#endif // FEAT_NO_READLINE
