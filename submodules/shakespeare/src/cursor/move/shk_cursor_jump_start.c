/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_cursor_jump_start.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 07:20:20 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/26 17:32:31 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shakespeare.h>

void	shk_cursor_jump_start(t_shakespeare_data *shk)
{
	shk_cursor_jump(shk, shk->draw.cursor_base_x
		+ shk_prompt_len(shk->draw.prompt),
		shk->draw.cursor_base_y);
}
