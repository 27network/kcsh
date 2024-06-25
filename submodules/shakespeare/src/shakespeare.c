/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shakespeare.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 05:37:56 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/25 07:32:39 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/print.h>
#include <ft/string/parse.h>
#include <ft/string.h>
#include <shakespeare.h>
#include <stdio.h>
#include <unistd.h>

static bool	shk_append_to_buffer(t_shakespeare_data *shk, char c)
{
	size_t	i;

	(void) write(shk->draw_ctx.output_fd, &c, 1);
	if (shk->buffer[shk->draw_ctx.cursor_pos])
	{
		i = shk->draw_ctx.cursor_pos;
		while (shk->buffer[i] && i < shk->buffer_size - 2)
		{
			shk->buffer[i + 1] = shk->buffer[i + 2];
			i++;
		}
	}
	shk->buffer[shk->draw_ctx.cursor_pos++] = c;
	shk->buffer_size++;
	if (shk->buffer_size >= shk->next_buffer_size - 2)
	{
		shk->next_buffer_size = shk->buffer_size + SHK_BUFFER_BLOCK_SIZE;
		shk->buffer = ft_realloc(shk->buffer, shk->buffer_size,
				shk->next_buffer_size);
	}
	return (shk->buffer != NULL);
}

static bool	shk_handle_char(t_shakespeare_data *shk, char c)
{
	// printf("c: %d (%0x)\n", c, c);
	if (c == 27)
		return (shk_handle_escape(shk));
	if (c == 4)
		ft_strdel(&shk->buffer);
	if (c == 4)
		return (false);
	if (c == '\n')
		return (shk_append_to_buffer(shk, '\n') && !!!true);
	if (c == 127)
		return (shk_cursor_backspace(shk));
	return (shk_append_to_buffer(shk, c));
}

static bool	shk_setup_cursor_base(t_shakespeare_data *shk)
{
	char	buf_write[33];
	char	*buf;
	char	*first;

	(void) write(1, "\033[6n", 4);
	buf = buf_write;
	ft_bzero(buf_write, 33);
	if (read(0, buf_write, 32) <= 0)
		return (false);
	buf_write[32] = '\0';
	while (*buf && *buf != '[')
		buf++;
	first = ft_strdup_range(buf, 1, ft_strchr(buf, ';') - buf);
	if (!first)
		perror("strdup_range");
	if (!first)
		return (false);
	shk->draw_ctx.cursor_base_y = ft_atoi(first);
	free(first);
	while (*buf && *buf != ';')
		buf++;
	if (*buf)
		buf++;
	shk->draw_ctx.cursor_base_x = ft_atoi(buf);
	return (true);
}

char	*shakespeare(const char *prompt)
{
	t_shakespeare_data	*shk;
	ssize_t				ret;

	shk = shk_shared();
	if (!shk_setup_cursor_base(shk))
		return (NULL);
	shk->buffer = ft_calloc(SHK_BUFFER_BLOCK_SIZE, sizeof(char));
	if (!shk->buffer)
		return (NULL);
	shk->history_cursor = NULL;
	shk->buffer_size = 0;
	shk->next_buffer_size = SHK_BUFFER_BLOCK_SIZE;
	shk->draw_ctx.prompt = prompt;
	shk_prompt_draw(prompt);
	shk->draw_ctx.cursor_pos = 0;
	while (1)
	{
		ret = read(0, &shk->read_buffer, 1);
		shk->read_buffer[1] = '\0';
		if (ret == -1)
			ft_strdel(&shk->buffer);
		if (ret == -1)
			break ;
		if (!shk_handle_char(shk, shk->read_buffer[0]))
			break ;
	}
	return (shk->buffer);
}
