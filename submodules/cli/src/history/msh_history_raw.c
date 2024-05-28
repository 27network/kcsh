/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_history_raw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 20:40:23 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/29 00:08:01 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <msh/cli/history.h>
#include <readline/readline.h>
#include <stdint.h>
#include <unistd.h>

#define HISTACCESS_WARNING "msh: warning: unable to access internal history, \
some features will be disabled\n"

HIST_ENTRY	***msh_history_raw(void)
{
	static HIST_ENTRY	***history_ptr = NULL;
	static bool			initialized = false;
	uint64_t			base_ptr;

	if (!initialized)
	{
		initialized = true;
		base_ptr = (uint64_t) & history_max_entries;
		history_ptr = (HIST_ENTRY ***)(base_ptr + 12);
		add_history("msh_history_raw");
		if (!history_ptr || !*history_ptr)
		{
			ft_putstr_fd(HISTACCESS_WARNING, STDERR_FILENO);
			history_ptr = NULL;
		}
		rl_clear_history();
	}
	return (history_ptr);
}
