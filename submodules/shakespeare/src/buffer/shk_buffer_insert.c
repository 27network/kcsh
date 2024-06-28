/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_buffer_insert.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 23:16:56 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/27 00:03:02 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shakespeare.h>

bool	shk_buffer_insert(t_shakespeare_data *shk, char c, size_t pos)
{
	const int	old_pos = shk->draw.cursor_pos;
	bool		ret;

	shk->draw.cursor_pos = pos;
	ret = shk_buffer_append(shk, c);
	shk->draw.cursor_pos = old_pos;
	return (ret);
}
