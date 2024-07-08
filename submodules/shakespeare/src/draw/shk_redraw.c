/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_redraw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 04:33:46 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/08 18:37:11 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <ft/string.h>
#include <shakespeare.h>
#include <unistd.h>

#if 1

static void	shk_draw_word(t_shakespeare_data *shk, const char *word,
				size_t len, size_t count)
{
	if (shk->hooks.draw_word_hook)
		shk->hooks.draw_word_hook(shk, SHK_HOOK_BEFORE, word, count);
	(void) !write(shk->draw.output_fd, word, len);
	if (shk->hooks.draw_word_hook)
		shk->hooks.draw_word_hook(shk, SHK_HOOK_AFTER, word, count);
}

static void	shk_redraw_words(t_shakespeare_data *shk)
{
	size_t		i;
	size_t		j;
	size_t		len;
	size_t		count;

	i = 0;
	count = 0;
	while (shk->buffer[i])
	{
		j = i;
		while (shk->buffer[j] && !ft_isspace(shk->buffer[j]))
			j++;
		len = j - i;
		shk_draw_word(shk, shk->buffer + i, len, count);
		count++;
		i = j;
		while (ft_isspace(shk->buffer[i]))
		{
			ft_putchar_fd(shk->buffer[i], shk->draw.output_fd);
			i++;
		}
	}
}

void	shk_redraw(t_shakespeare_data *shk)
{
	ft_putstr_fd("\033[?25l", shk->draw.output_fd);
	if (shk->hooks.draw_hook && shk->hooks.draw_hook(shk, SHK_HOOK_BEFORE))
	{
		ft_putstr_fd("\033[?25h", shk->draw.output_fd);
		return ;
	}
	shk_prompt_draw(shk, shk->draw.prompt);
	ft_putstr_fd("\033[J", shk->draw.output_fd);
	if (!shk->hooks.draw_word_hook && false)
		ft_putstr_fd(shk->buffer, shk->draw.output_fd);
	else
		shk_redraw_words(shk);
	if (shk->hooks.draw_hook)
		shk->hooks.draw_hook(shk, SHK_HOOK_AFTER);
	ft_putstr_fd("\033[?25h", shk->draw.output_fd);
	shk_cursor_jump_logical(shk);
}

#else

void	shk_redraw(t_shakespeare_data *shk)
{
	size_t	cx;
	size_t	cy;

	if (shk->hooks.draw_hook && shk->hooks.draw_hook(shk, SHK_HOOK_BEFORE))
		return ;
	shk_cursor_pos(shk, &cx, &cy);
	shk_prompt_draw(shk, shk->draw.prompt);
	if (shk->draw.cursor_pos)
		ft_dprintf(shk->draw.output_fd, "%s%s",
			"\033[J", shk->buffer + shk->draw.cursor_pos - 1);
	if (shk->hooks.draw_hook)
		shk->hooks.draw_hook(shk, SHK_HOOK_AFTER);
}

#endif
