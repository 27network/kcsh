/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_termios_reset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 23:02:49 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/26 23:02:57 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shakespeare.h>

void	shk_termios_reset(t_shakespeare_data *shk)
{
	tcsetattr(0, TCSAFLUSH, &shk->old_termios);
}
