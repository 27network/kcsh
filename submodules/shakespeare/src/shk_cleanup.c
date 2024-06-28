/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 06:14:33 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/27 01:20:46 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <shakespeare.h>
#include <stdlib.h>

__attribute__((destructor))
static void	shk_cleanup(void)
{
	t_shakespeare_data	*shk;

	shk = shk_shared();
	if (!shk->initialized)
		return ;
	shk_history_clear();
	shk->initialized = false;
}
