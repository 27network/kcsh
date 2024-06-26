/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_prompt_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 05:35:30 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/26 14:43:19 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <shakespeare.h>

void	shk_prompt_draw(const char *prompt)
{
	t_shakespeare_data	*shk;
	int					escaped;

	shk = shk_shared();
	shk_cursor_jump_abs(shk->draw_ctx.cursor_base_x,
		shk->draw_ctx.cursor_base_y);
	escaped = 0;
	while (*prompt)
	{
		if (*prompt == '\001')
			escaped++;
		else if (*prompt == '\002')
		{
			if (escaped > 0)
				escaped--;
		}
		else if (escaped == 0)
			ft_putchar_fd(*prompt, 1);
		prompt++;
	}
}
