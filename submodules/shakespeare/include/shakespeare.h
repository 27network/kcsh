/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shakespeare.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 05:43:33 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/26 14:45:38 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAKESPEARE_H
# define SHAKESPEARE_H
# undef SHAKESPEARE_H
# ifndef __SHAKESPEARE_H__
#  define __SHAKESPEARE_H__

#  include <termios.h>
#  include <term.h>
#  include <stdbool.h>
#  include <stddef.h>
#  include <sys/ioctl.h>

#  define SHK_BUFFER_BLOCK_SIZE 32

// #  define CTL(x)          ((x) & 0x1F)
// #  define ISCTL(x)        ((x) && (x) < ' ')
// #  define UNCTL(x)        ((x) + 64)
// #  define META(x)         ((x) | 0x80)
// #  define ISMETA(x)       ((x) & 0x80)
// #  define UNMETA(x)       ((x) & 0x7F)

typedef struct s_history_entry
{
	char					*line;
	size_t					length;
	struct s_history_entry	*prev;
	struct s_history_entry	*next;
}	t_history_entry;

typedef struct s_drawing_context
{
	int				output_fd;
	char			*backspace;
	int				tty_cols;
	int				tty_rows;
	const char		*prompt;

	int				cursor_pos;
	size_t			cursor_base_x;
	size_t			cursor_base_y;
	size_t			line_start_x;
	size_t			line_start_y;
}	t_draw_ctx;

typedef struct s_shakespeare_data
{
	bool			initialized;

	char			*buffer;
	size_t			buffer_size;
	size_t			next_buffer_size;
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

bool				shk_handle_escape(t_shakespeare_data *shk);

void				shk_history_clear(void);
t_history_entry		*shk_history_pop(void);
void				shk_history_push(const char *line);

void				shk_cursor_pos(t_shakespeare_data *shk,
						size_t *x, size_t *y);
void				shk_redraw(void);
void				shk_redraw_after(void);

bool				shk_cursor_backspace(t_shakespeare_data *shk);
bool				shk_cursor_delete(t_shakespeare_data *shk);

void				shk_cursor_backward(int n);
void				shk_cursor_forward(int n);

void				shk_cursor_jump(t_shakespeare_data *shk, size_t x,
						size_t y);
void				shk_cursor_jump_end(t_shakespeare_data *shk);
void				shk_cursor_jump_start(t_shakespeare_data *shk);

void				shk_cursor_jump_abs(size_t x, size_t y);

void				shk_prompt_draw(const char *prompt);
size_t				shk_prompt_len(const char *prompt);

# endif // __SHAKESPEARE_H__
#endif // SHAKESPEARE_H
