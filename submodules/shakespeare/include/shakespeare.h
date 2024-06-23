/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shakespeare.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 05:43:33 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/23 07:05:42 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAKESPEARE_H
# define SHAKESPEARE_H
# undef SHAKESPEARE_H
# ifndef __SHAKESPEARE_H__
#  define __SHAKESPEARE_H__

#  include <termios.h>
#  include <stdbool.h>
#  include <stddef.h>
#  include <sys/ioctl.h>

#  define SHK_BUFFER_BLOCK_SIZE 32

typedef struct s_history_entry
{
	char					*line;
	size_t					length;
	struct s_history_entry	*prev;
	struct s_history_entry	*next;
}	t_history_entry;

typedef struct s_drawing_context
{
	struct winsize	terminal_size;
	size_t			cursor_x;
	size_t			cursor_y;
	size_t			line_start_x;
	size_t			line_start_y;
}	t_draw_ctx;

typedef struct s_shakespeare_data
{
	bool			initialized;

	char			*buffer;
	size_t			buffer_size;
	char			read_buffer[2];

	t_history_entry	*history_stack;
	t_history_entry	*history_cursor;

	t_draw_ctx		draw_ctx;

	struct termios	old_termios;
	struct termios	new_termios;
}	t_shakespeare_data;

char				*shakespeare(const char *prompt);

void				shk_init(t_shakespeare_data *shk);
t_shakespeare_data	*shk_shared(void);

void				shk_history_clear(void);
t_history_entry		*shk_history_pop(void);
void				shk_history_push(const char *line);

# endif // __SHAKESPEARE_H__
#endif // SHAKESPEARE_H
