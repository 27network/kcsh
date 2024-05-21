/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_is_interactive.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 05:02:54 by kiroussa          #+#    #+#             */
/*   Updated: 2024/03/22 17:57:30 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/io.h>
#include <readline/readline.h>
#include <unistd.h>

bool	msh_is_interactive(void)
{
	int	tty;

	tty = STDIN_FILENO;
	if (rl_instream)
		tty = msh_fileno(rl_instream);
	return (isatty(tty));
}
