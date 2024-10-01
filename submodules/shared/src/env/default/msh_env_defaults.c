/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_defaults.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouchet <ebouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 23:15:34 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/01 10:56:29 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string/parse.h>
#include <ft/string.h>
#include <msh/env.h>
#include <msh/util.h>
#include <unistd.h>

void	msh_env_setup_pwd(t_minishell *msh);
void	msh_env_adjust_shlvl(t_minishell *msh, int change);
void	msh_env_setup_userdata(t_minishell *msh, int uid);

static void	msh_env_setup_readonly(t_minishell *msh, int uid)
{
	msh_env_set_if_not(msh, "UID", ft_itoa(uid), ENV_ALLOC_VALUE
		| ENV_READONLY);
	msh_env_set_if_not(msh, "EUID", ft_itoa(msh_geteuid(msh)), ENV_ALLOC_VALUE
		| ENV_READONLY);
}

void	msh_env_defaults(t_minishell *msh)
{
	const int	uid = msh_getuid(msh);

	msh_env_set_if_not(msh, "PATH", ENV_DEFAULT_PATH, 0);
	msh_env_setup_userdata(msh, uid);
	msh_env_setup_pwd(msh);
	msh_env_set_if_not(msh, "TERM", ENV_DEFAULT_TERM, 0);
	msh_env_set_if_not(msh, "PS1", ENV_DEFAULT_PS1, 0);
	msh_env_set_if_not(msh, "PS2", ENV_DEFAULT_PS2, 0);
	msh_env_set_if_not(msh, "PS3", ENV_DEFAULT_PS3, 0);
	msh_env_set_if_not(msh, "PS4", ENV_DEFAULT_PS4, 0);
	msh_env_set_if_not(msh, "HISTFILE", msh_expand_tilde(msh,
			ENV_DEFAULT_HISTFILE), ENV_ALLOC_VALUE);
	msh_env_push(msh, "IFS", ENV_DEFAULT_IFS, 0);
	msh_env_set_if_not(msh, "HOSTTYPE", msh_get_hosttype(msh), ENV_ALLOC_VALUE);
	msh_env_adjust_shlvl(msh, 1);
	msh_env_set_if_not(msh, "_", msh->binary_name, ENV_EXPORTED
		| ENV_INVISIBLE);
	msh_env_setup_readonly(msh, uid);
}
