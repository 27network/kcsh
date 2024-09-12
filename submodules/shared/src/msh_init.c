/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 01:45:29 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/21 17:53:07 by kiroussa         ###   ########.fr       */
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

static void	msh_init_flags(t_minishell *msh)
{
	char	*posix;

	posix = msh_env_value(msh, "POSIXLY_CORRECT");
	if (posix == NULL)
		posix = msh_env_value(msh, "POSIX_PEDANTIC");
	if (posix != NULL)
		msh->flags.posix = true;
	if (msh->flags.posix)
		msh_env_push(msh, "POSIXLY_CORRECT", "y", ENV_EXPORTED);
	if (msh->binary_name[0] == '-')
	{
		msh->binary_name++;
		msh->flags.login = true;
		if (msh->binary_name[0] == 0)
			msh->binary_name = MSH_DEFAULT_NAME;
	}
	if (!msh->interactive || !ft_strchr(msh->binary_name, '/'))
		msh->name = msh->binary_name;
	else
		msh->name = ft_strrchr(msh->binary_name, '/') + 1;
	if (!msh->name)
		msh->name = MSH_DEFAULT_NAME;
}

void	msh_init(
	t_minishell *msh,
	[[maybe_unused]] int argc,
	const char **argv,
	const char **envp
) {
	ft_bzero(msh, sizeof(t_minishell));
	msh->binary_name = argv[0];
	msh->interactive = msh_is_interactive(msh);
	if (msh->interactive && !msh_fetch_term(msh))
	{
		msh_error(msh, "failed to fetch termios\n");
		msh_exit(msh, -1);
	}
	if (!msh_env_populate(msh, envp))
	{
		msh_error(msh, "failed to populate env\n");
		msh_exit(msh, -2);
	}
	msh_init_flags(msh);
	msh_env_defaults(msh);
	msh_get_hostname(msh);
	msh->execution_context.running = true;
	msh->execution_context.line = 0;
}
