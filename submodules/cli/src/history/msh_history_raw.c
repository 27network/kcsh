/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_history_raw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 20:40:23 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/30 15:43:56 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/print.h>
#include <msh/cli/history.h>
#include <readline/readline.h>
#include <stdint.h>
#include <unistd.h>

#define HISTACCESS_WARNING "msh: warning: unable to access internal history, \
some features will be disabled\n"

/**
 * @brief Fetches the pointer to readline's `the_history`.
 *
 * @note This is done by reading the offset from the `history_list` function
 *		 directly in assembly. We read the `history_list` function, we then
 *       skip `endbr64` (+4), the `mov` opcode (+1), the `mov` intrinsics (+2),
 *       and read the int offset from %rsi (function address + 4). We then add
 *       the offset to the function address to get the pointer to `the_history`.
 *
 * @return uint64_t The pointer.
 */
static HIST_ENTRY	***msh_fetch_pointer(void)
{
	uint64_t	offset;
	void		*base_ptr;
	int			*offset_ptr;
	HIST_ENTRY	***the_history;
	int			endbr64_offset;

	base_ptr = (void *)(&history_list);
	endbr64_offset = 0;
	if (*(unsigned char *)base_ptr == 243)
		endbr64_offset = 4;
	offset_ptr = (int *)(base_ptr + endbr64_offset + 1 + 2);
	offset = *offset_ptr;
	the_history = (HIST_ENTRY ***)(base_ptr + endbr64_offset + 7 + offset);
	return (the_history);
}

HIST_ENTRY	***msh_history_raw(void)
{
	static HIST_ENTRY	***history_ptr = NULL;
	static bool			initialized = false;

	if (!initialized)
	{
		initialized = true;
		history_ptr = msh_fetch_pointer();
		if (!history_ptr || *history_ptr)
		{
			ft_dprintf(STDERR_FILENO, HISTACCESS_WARNING);
			history_ptr = NULL;
		}
	}
	return (history_ptr);
}
