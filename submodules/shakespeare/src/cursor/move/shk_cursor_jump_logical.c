/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_cursor_jump_logical.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:19:59 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/27 15:36:35 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shakespeare.h>

#include <stdio.h>

void	shk_cursor_jump_logical(t_shakespeare_data *shk)
{
	size_t	cursor_x;
	size_t	cursor_y;

	shk_cursor_pos(shk, &cursor_x, &cursor_y);
	// printf("jumping to %zu, %zu\n", cursor_x, cursor_y);
	shk_cursor_jump_abs(shk, cursor_x, cursor_y);
}
