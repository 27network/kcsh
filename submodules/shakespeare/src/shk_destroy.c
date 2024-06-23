/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 06:14:33 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/23 06:49:33 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shakespeare.h>

#include <stdio.h>

__attribute__((destructor))
static void	shk_destroy(void)
{
	t_shakespeare_data	*shk;

	printf("shk_destroy\n");
	shk = shk_shared();
	if (!shk->initialized)
		return ;
	tcsetattr(0, TCSAFLUSH, &shk->old_termios);
	shk->initialized = false;
	shk_history_clear();
}
