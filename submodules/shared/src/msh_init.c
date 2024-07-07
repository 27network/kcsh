/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 01:45:29 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/07 02:12:05 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/print.h>
#include <ft/string.h>
#include <msh/env.h>
#include <msh/util.h>
#include <msh/log.h>
#include <msh/minishell.h>
#include <unistd.h>

static bool	msh_fetch_term(t_minishell *msh)
{
	if (tcgetattr(STDIN_FILENO, &msh->term) == -1)
		return (false);
	return (true);
}

void	msh_init(
	t_minishell *msh,
	__attribute__((unused)) int argc,
	const char **argv,
	const char **envp
) {
	ft_bzero(msh, sizeof(t_minishell));
	msh->binary_name = argv[0];
	msh->name = argv[0];
	msh->interactive = msh_is_interactive();
	msh->forked = false;
	if (!msh_fetch_term(msh))
	{
		msh_error(msh, "failed to fetch termios\n");
		msh_exit(msh, -1);
	}
	if (!msh_env_populate(msh, envp))
	{
		msh_error(msh, "failed to populate env\n");
		msh_exit(msh, -2);
	}
	msh_env_defaults(msh);
	msh_get_hostname(msh);
	msh->execution_context.running = true;
	msh->execution_context.line = 0;
}
