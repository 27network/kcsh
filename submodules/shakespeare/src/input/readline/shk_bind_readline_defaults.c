/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_bind_readline_defaults.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 01:28:11 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/02 16:10:13 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shakespeare.h>

// 42sh: C-b, C-f, C-p, C-n, C-_, C-t, A-t
// readline: C-l C-a C-e C-d

void	shk_bind_readline_defaults(t_shakespeare_data *shk)
{
	shk_input_bind(shk, BIND_READLINE_ONLY, "C-b", &shk_cursor_backward);
	shk_input_bind(shk, BIND_READLINE_ONLY, "C-f", &shk_cursor_forward);
	shk_input_bind(shk, BIND_READLINE_ONLY, "C-p", &shk_history_prev);
	shk_input_bind(shk, BIND_READLINE_ONLY, "C-n", &shk_history_next);
	shk_input_bind(shk, BIND_READLINE_ONLY, "C-_", &shk_buffer_undo);
	shk_input_bind(shk, BIND_READLINE_ONLY, "C-t", &shk_cursor_swap);
	shk_input_bind(shk, BIND_READLINE_ONLY, "A-t", &shk_cursor_swap_word);
	shk_input_bind(shk, BIND_READLINE_ONLY, "C-l", &shk_terminal_clear);
	shk_input_bind(shk, BIND_READLINE_ONLY, "C-a", &shk_cursor_jump_start);
	shk_input_bind(shk, BIND_READLINE_ONLY, "C-e", &shk_cursor_jump_end);
	shk_input_bind(shk, BIND_READLINE_ONLY, "C-d", &shk_cursor_delete);
}
