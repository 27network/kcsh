/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_prompt_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 05:35:30 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/09 15:01:02 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <shakespeare.h>

void	shk_prompt_draw(t_shakespeare_data *shk, const char *prompt)
{
	int					escaped;

	shk_cursor_jump_abs(shk, shk->draw.cursor_base_x,
		shk->draw.cursor_base_y);
	escaped = false;
	while (*prompt)
	{
		if (*prompt == '\001')
			escaped = true;
		else if (*prompt == '\002' && escaped)
			escaped = false;
		else if (!escaped)
			ft_putchar_fd(*prompt, 1);
		prompt++;
	}
}
