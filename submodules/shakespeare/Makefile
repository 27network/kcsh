# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/23 05:37:35 by kiroussa          #+#    #+#              #
#    Updated: 2024/06/27 16:53:28 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	shakespeare

include ../common-prelude.mk

SRC			=	buffer/shk_buffer_append.c \
				buffer/shk_buffer_insert.c \
				buffer/shk_buffer_height.c \
				cursor/act/shk_cursor_backspace.c \
				cursor/act/shk_cursor_delete.c \
				cursor/move/shk_cursor_backward.c \
				cursor/move/shk_cursor_forward.c \
				cursor/move/shk_cursor_jump.c \
				cursor/move/shk_cursor_jump_abs.c \
				cursor/move/shk_cursor_jump_end.c \
				cursor/move/shk_cursor_jump_logical.c \
				cursor/move/shk_cursor_jump_start.c \
				cursor/shk_cursor_pos.c \
				cursor/shk_cursor_pos_abs.c \
				draw/prompt/shk_prompt_draw.c \
				draw/prompt/shk_prompt_len.c \
				draw/shk_redraw.c \
				draw/shk_redraw_after.c \
				history/shk_history_clear.c \
				history/shk_history_pop.c \
				history/shk_history_push.c \
				input/shk_handle_escape.c \
				shakespeare.c \
				shk_cleanup.c \
				shk_init.c \
				shk_reset.c \
				shk_shared.c \
				shk_termios_reset.c \
				shk_termios_setup.c \
				shk_window_update_size.c

include ../common.mk
