/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 01:45:29 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/29 22:43:18 by kiroussa         ###   ########.fr       */
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
	if (!msh_env_populate(msh, envp))
	{
		msh_error(msh, "failed to populate env");
		msh_exit(msh, -2);
	}
	msh_env_defaults(msh);
	msh->execution_context.running = true;
	msh->execution_context.line = 0;
}
