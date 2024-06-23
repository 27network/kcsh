/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shakespeare.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 05:37:56 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/23 06:53:52 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shakespeare.h>

#include <ft/mem.h>
#include <ft/print.h>
#include <ft/string.h>
#include <unistd.h>

#include <stdio.h>

static bool	shk_handle_char(t_shakespeare_data *shk, char c)
{
	// printf("shk_handle_char: %c (%#x)\n", c, c);
	if (c == 4)
		ft_strdel(&shk->buffer);
	if (c == '\n')
		(void) write(2, "\n", 1);
	if (c == 4 || c == '\n')
		return (false);
	if (c == 127)
	{
		if (shk->buffer[0])
			(void) write(2, "\b \b", 3);
		if (shk->buffer[0])
			shk->buffer[ft_strlen(shk->buffer) - 1] = '\0';
		return (true);
	}
	(void) write(2, &c, 1);
	shk->buffer[shk->buffer_size++] = c;
	if (shk->buffer_size % SHK_BUFFER_BLOCK_SIZE == 0)
	{
		shk->buffer = ft_realloc(shk->buffer, shk->buffer_size, shk->buffer_size
				+ SHK_BUFFER_BLOCK_SIZE);
		if (!shk->buffer)
			return (false);
	}
	return (shk->buffer != NULL);
}

char	*shakespeare(const char *prompt)
{
	t_shakespeare_data	*shk;
	ssize_t				ret;

	shk = shk_shared();
	shk->buffer = ft_calloc(SHK_BUFFER_BLOCK_SIZE, sizeof(char));
	shk->history_cursor = NULL;
	shk->buffer_size = 0;
	if (!shk->buffer)
		return (NULL);
	ft_putstr_fd(prompt, 2);
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
