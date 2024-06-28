/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signal_handler_interactive.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:04:43 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/28 23:21:33 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <msh/signal.h>
#include <msh/features.h>
#if FEAT_NO_READLINE
# include <shakespeare.h>
#else
# include <stdio.h>
# include <readline/readline.h>
#endif // FEAT_NO_READLINE

#if FEAT_NO_READLINE

static void	msh_linelib_newline(void)
{
	t_shakespeare_data	*shk;

	shk = shk_shared();
	ft_putstr("\r\n");
	shk_reset(shk, shk->draw.prompt);
	shk_prompt_draw(shk, shk->draw.prompt);
}

#else

static void	msh_linelib_newline(void)
{
	ft_putstr("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

#endif // FEAT_NO_READLINE

void	msh_signal_handler_interactive(int signo)
{
	g_signal = signo;
	if (signo == SIGINT)
		msh_linelib_newline();
}
