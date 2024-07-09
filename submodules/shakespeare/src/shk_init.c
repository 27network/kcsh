/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 06:08:33 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/09 15:05:09 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/colors.h>
#include <ft/mem.h>
#include <ft/print.h>
#include <shakespeare.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void	shk_signal_handler(int signum)
{
	t_shakespeare_data	*shk;

	if (signum == SIGWINCH)
	{
		shk = shk_shared();
		shk_window_update_size(shk);
		shk_redraw(shk);
	}
}

static void	shk_setup_signals(void)
{
	signal(SIGWINCH, shk_signal_handler);
}

static bool	shk_input_hook_dev(
	t_shakespeare_data *shk,
	const t_shk_hook_type type,
	const char c,
	bool *ret
) {
	(void) ret;
	if (type == SHK_HOOK_BEFORE)
		ft_dprintf(shk->draw.output_fd, "read: %c (%0x)\n", c, c);
	return (false);
}

__attribute__((unused))
static void	shk_draw_word_hook(
	t_shakespeare_data *shk,
	const t_shk_hook_type type,
	const char *word,
	const size_t index
) {
	char	*s;

	(void) word;
	if (type == SHK_HOOK_BEFORE)
	{
		if (index == 0)
			s = B_RED;
		else
			s = UNDERLINE;
	}
	else if (type == SHK_HOOK_AFTER)
		s = RESET;
	else
		return ;
	ft_putstr_fd(s, shk->draw.output_fd);
}

bool	shk_init(t_shakespeare_data *shk)
{
	if (shk->initialized)
	{
		ft_dprintf(STDERR_FILENO, "shk_init: already initialized\n");
		return (false);
	}
	ft_bzero(shk, sizeof(t_shakespeare_data));
	shk->initialized = true;
	shk->draw.output_fd = STDERR_FILENO;
	if (getenv("SHK_DEBUG"))
		shk->hooks.input_hook = shk_input_hook_dev;
	shk_setup_signals();
	return (true);
}
