/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_termios_setup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 22:51:35 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/28 15:48:55 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shakespeare.h>
#include <unistd.h>

bool	shk_termios_setup(t_shakespeare_data *shk)
{
	if (tcgetattr(STDIN_FILENO, &shk->old_termios) == -1)
		return (false);
	shk->new_termios = shk->old_termios;
	shk->new_termios.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	shk->new_termios.c_lflag &= ~(ICANON | ECHO | ISIG | IEXTEN);
	shk->new_termios.c_cflag |= (CS8);
	shk->new_termios.c_cc[VMIN] = 1;
	shk->new_termios.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &shk->new_termios) == -1)
		return (false);
	return (true);
}
