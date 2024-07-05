/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shakespeare.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 05:43:33 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/02 19:13:22 by kiroussa         ###   ########.fr       */
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
#  include <wchar.h>

#  define SHK_BUFFER_BLOCK_SIZE 32

// #  define CTL(x)          ((x) & 0x1F)
// #  define ISCTL(x)        ((x) && (x) < ' ')
// #  define UNCTL(x)        ((x) + 64)
// #  define META(x)         ((x) | 0x80)
// #  define ISMETA(x)       ((x) & 0x80)
// #  define UNMETA(x)       ((x) & 0x7F)

typedef struct s_shakespeare_data	t_shakespeare_data;

// Hooks

typedef enum e_shk_hook_type
{
	SHK_HOOK_BEFORE = 0,
	SHK_HOOK_AFTER,
}	t_shk_hook_type;

/**
 * @brief Hooks into the drawing process.
 *
 * @param shk The Shakespeare data structure.
 * @param type The type of hook.
 *
 * @return true if the draw should be cancelled (type `SHK_HOOK_BEFORE` only)
 */
typedef bool						t_shk_hook_draw(
										t_shakespeare_data *shk,
										const t_shk_hook_type type);

/**
 * @brief Hooks into the word drawing process.
 *
 * @param shk The Shakespeare data structure.
 * @param type The type of hook.
 * @param word The word to draw.
 * @param index The index of the word in the buffer.
 */
typedef void						t_shk_hook_draw_word(
										t_shakespeare_data *shk,
										t_shk_hook_type type,
										const char *word,
										const size_t index);

/**
 * @brief Hooks into the input handling process.
 *
 * @param shk The Shakespeare data structure.
 * @param type The type of hook.
 * @param input The input character.
 * @param ret Whether to eagerly return the input.
 *
 * @return true if the function provides input handling
 *		   and cancels the default behavior. (type `SHK_HOOK_BEFORE` only)
 */
typedef bool						t_shk_hook_input(
										t_shakespeare_data *shk,
										const t_shk_hook_type type,
										const char input,
										bool *ret);

typedef struct s_shk_hooks
{
	t_shk_hook_draw			*draw_hook;
	t_shk_hook_draw_word	*draw_word_hook;
	t_shk_hook_input		*input_hook;
}	t_shk_hooks;

// History

typedef struct s_history_entry
{
	char					*line;
	size_t					length;
	struct s_history_entry	*prev;
	struct s_history_entry	*next;
}	t_history_entry;

// Drawing

typedef struct s_shk_draw_ctx
{
	int				output_fd;
	int				tty_cols;
	int				tty_rows;
	const char		*prompt;

	int				cursor_pos;
	size_t			cursor_base_x;
	size_t			cursor_base_y;
	size_t			line_start_x;
	size_t			line_start_y;

	size_t			old_draw_size;
}	t_shk_draw_ctx;

// Input

typedef void						t_shk_input_action(
										t_shakespeare_data *shk,
										int n);

#  define BIND_READLINE_ONLY 1
#  define BIND_VIM_ONLY 2
#  define BIND_BOTH 3

typedef struct s_shk_input_bind
{
	char				key[256];
	size_t				combo_size;
	int					mode_target;
	t_shk_input_action	*action_fn;
}	t_shk_input_bind;

typedef struct s_shk_input_mgr
{
	t_shk_input_bind	*binds;
	size_t				binds_size;
	size_t				binds_capacity;
	int					current_mode;
}	t_shk_input_mgr;

// Main data structure

typedef struct s_shakespeare_data
{
	bool			initialized;

	char			*buffer;
	char			*buffer_save;
	size_t			buffer_size;
	size_t			next_buffer_size;
	char			read_buffer[2];

	t_history_entry	*history_stack;
	t_history_entry	*history_current;

	t_shk_hooks		hooks;
	t_shk_draw_ctx	draw;
	t_shk_input_mgr	input;

	struct termios	old_termios;
	struct termios	new_termios;
}	t_shakespeare_data;

// Global functions

char				*shakespeare(const char *prompt);

// Internal functions

t_shakespeare_data	*shk_shared(void);
bool				shk_init(t_shakespeare_data *shk);
bool				shk_reset(t_shakespeare_data *shk, const char *prompt);
bool				shk_termios_setup(t_shakespeare_data *shk);
void				shk_termios_reset(t_shakespeare_data *shk);
void				shk_window_update_size(t_shakespeare_data *shk);

bool				shk_handle_char(t_shakespeare_data *shk, char c);

// Buffer interaction

bool				shk_buffer_append(t_shakespeare_data *shk, char c);
bool				shk_buffer_insert(t_shakespeare_data *shk, char c,
						size_t pos);
size_t				shk_buffer_height(t_shakespeare_data *shk);

// Cursor interaction

bool				shk_cursor_backspace(t_shakespeare_data *shk, int n);
bool				shk_cursor_delete(t_shakespeare_data *shk, int n);

void				shk_cursor_backward(t_shakespeare_data *shk, int n);
void				shk_cursor_forward(t_shakespeare_data *shk, int n);

void				shk_cursor_jump(t_shakespeare_data *shk, size_t x,
						size_t y);
void				shk_cursor_jump_end(t_shakespeare_data *shk);
void				shk_cursor_jump_start(t_shakespeare_data *shk);

void				shk_cursor_jump_abs(t_shakespeare_data *shk,
						size_t x, size_t y);
void				shk_cursor_jump_logical(t_shakespeare_data *shk);

void				shk_cursor_pos(t_shakespeare_data *shk,
						size_t *x, size_t *y);
bool				shk_cursor_pos_abs(t_shakespeare_data *shk,
						size_t *x, size_t *y);
// Drawing

void				shk_redraw(t_shakespeare_data *shk);
void				shk_redraw_after(t_shakespeare_data *shk);

void				shk_prompt_draw(t_shakespeare_data *shk,
						const char *prompt);
size_t				shk_prompt_len(const char *prompt);

// History

void				shk_history_clear(void);
t_history_entry		*shk_history_pop(void);
void				shk_history_push(const char *line);
void				shk_history_modify_last(const char *line);

// Input

bool				shk_handle_escape(t_shakespeare_data *shk);

# endif // __SHAKESPEARE_H__
#endif // SHAKESPEARE_H
