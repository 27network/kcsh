/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_terminal_clear.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 01:32:57 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/02 15:45:56 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <shakespeare.h>

bool	shk_setup_cursor_base(t_shakespeare_data *shk);

void	shk_terminal_clear(t_shakespeare_data *shk, int n)
{
	(void) n;
	ft_putstr_fd("\033[2J\033[H", shk->draw.output_fd);
	shk->draw.cursor_base_x = 0;
	shk->draw.cursor_base_y = 0;
	shk_prompt_draw(shk, shk->draw.prompt);
}
