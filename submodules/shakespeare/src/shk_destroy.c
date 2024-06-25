/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 06:14:33 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/25 15:42:38 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <shakespeare.h>
#include <stdlib.h>

#include <stdio.h>

__attribute__((destructor))
static void	shk_destroy(void)
{
	t_shakespeare_data	*shk;

	shk = shk_shared();
	if (!shk->initialized)
		return ;
	tcsetattr(0, TCSAFLUSH, &shk->old_termios);
	if (shk->draw_ctx.backspace)
		free(shk->draw_ctx.backspace);
	shk_history_clear();
	shk->initialized = false;
}
