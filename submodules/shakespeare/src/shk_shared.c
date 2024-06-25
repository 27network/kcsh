/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_shared.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 06:14:59 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/25 15:10:49 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shakespeare.h>

t_shakespeare_data	*shk_shared(void)
{
	static t_shakespeare_data	data = {0};

	if (!data.initialized)
		shk_init(&data);
	return (&data);
}
