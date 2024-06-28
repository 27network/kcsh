/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_input_default_readline.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 01:28:11 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/27 15:03:22 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shakespeare.h>

// 42sh: C-b, C-f, C-p, C-n, C-_, C-t, A-t
// readline: C-l C-a C-e C-d

__attribute__((constructor))
void	shk_input_default_readline(void)
{
	t_shakespeare_data	*shk;

	shk = shk_shared();
	shk_input_bind(shk, "C-b", &shk_cursor_backward);
	shk_input_bind(shk, "C-f", &shk_cursor_forward);
	shk_input_bind(shk, "C-p", &shk_history_prev);
	shk_input_bind(shk, "C-n", &shk_history_next);
	shk_input_bind(shk, "C-_", &shk_buffer_undo);
	shk_input_bind(shk, "C-t", &shk_cursor_swap);
	shk_input_bind(shk, "A-t", &shk_cursor_swap_word);
	shk_input_bind(shk, "C-l", &shk_terminal_clear);
	shk_input_bind(shk, "C-a", &shk_cursor_jump_start);
	shk_input_bind(shk, "C-e", &shk_cursor_jump_end);
	shk_input_bind(shk, "C-d", &shk_cursor_delete);
}
