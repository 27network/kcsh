/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_is_interactive.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 05:02:54 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/28 23:13:30 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/features.h>
#include <msh/util.h>
#include <readline/readline.h>
#include <unistd.h>

bool	msh_is_interactive(void)
{
	int	tty;

	tty = STDIN_FILENO;
	if (!FEAT_NO_READLINE && rl_instream)
		tty = msh_fileno(rl_instream);
	return (isatty(tty));
}
