/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_history_save.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:32:03 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/21 17:07:34 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/features.h>
#include <msh/cli/history.h>
#if FEAT_HISTORY_FILE 
# include <fcntl.h>
# include <ft/print.h>
# include <msh/log.h>
# include <unistd.h>

# if FEAT_NO_READLINE
#  define LINELOG_SAVE msh_save_shakespeare

static bool	msh_save_shakespeare(
	t_minishell *msh,
	[[maybe_unused]] int fd
) {
	msh_error(msh, "shakespeare history saving not implemented\n");
	return (true);
}

# else
#  define LINELOG_SAVE msh_save_readline

static bool	msh_save_readline(
	[[maybe_unused]] t_minishell *msh,
	int fd
) {
	HIST_ENTRY	***history_ptr;
	HIST_ENTRY	**history;
	bool		error;
	int			i;

	history_ptr = msh_history_raw();
	if (!history_ptr || !*history_ptr)
		return (false);
	error = false;
	history = *history_ptr;
	i = 0;
	while (!error && history[i])
	{
		if (history[i]->line && *history[i]->line)
		{
			if (ft_dprintf(fd, "%s\n", history[i]->line) <= 0)
				error = true;
		}
		i++;
	}
	return (error);
}

# endif // FEAT_NO_READLINE

void	msh_history_save(t_minishell *msh)
{
	int			fd;

	if (!msh->interactive || msh->forked)
		return ;
	fd = msh_history_file(msh, O_CREAT | O_TRUNC | O_WRONLY);
	if (fd < 0)
		return ;
	if (LINELOG_SAVE(msh, fd))
		msh_error(msh, "failed to save history properly to file\n");
	if (close(fd) >= 0)
		msh_log(msh, MSG_DEBUG_GENERIC, "saved history to file successfully\n");
}

#else

void	msh_history_save([[maybe_unused]] t_minishell *msh)
{
}

#endif // FEAT_HISTORY_FILE
