/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_defaults.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 23:15:34 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/05 21:32:11 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string/parse.h>
#include <ft/string.h>
#include <msh/env.h>
#include <msh/util.h>

static void	msh_env_setup_pwd(t_minishell *msh)
{
	t_variable	*v_pwd;
	t_variable	*v_home;

	v_pwd = msh_env_get(msh, "PWD", 0);
	v_home = msh_env_find(msh, "HOME");
	//TODO: this fucker
	(void) v_home;
	v_pwd->flags |= ENV_EXPORTED;
}

static void	msh_env_adjust_shlvl(t_minishell *msh, int change)
{
	char		*old_shlvl;
	int			shlvl;

	old_shlvl = msh_env_value(msh, "SHLVL");
	if (!old_shlvl || !*old_shlvl)
		old_shlvl = "0";
	shlvl = ft_atoi(old_shlvl);
	shlvl += change;
	if (shlvl < 0)
		shlvl = 0;
	else if (shlvl >= 1000)
		shlvl = 1;
	msh_env_push(msh, "SHLVL", ft_itoa(shlvl), ENV_EXPORTED | ENV_ALLOC_VALUE);
}

void	msh_env_defaults(t_minishell *msh)
{
	msh_env_setup_pwd(msh);
	msh_env_set_if_not(msh, "_", msh->binary_name, ENV_EXPORTED
		| ENV_INVISIBLE);
	msh_env_set_if_not(msh, "PATH", ENV_DEFAULT_PATH, 0);
	msh_env_set_if_not(msh, "TERM", ENV_DEFAULT_TERM, 0);
	msh_env_set_if_not(msh, "PS1", ENV_DEFAULT_PS1, 0);
	msh_env_set_if_not(msh, "PS2", ENV_DEFAULT_PS2, 0);
	msh_env_set_if_not(msh, "PS3", ENV_DEFAULT_PS3, 0);
	msh_env_set_if_not(msh, "PS4", ENV_DEFAULT_PS4, 0);
	msh_env_set_if_not(msh, "HISTFILE", msh_expand_tilde(msh,
			ENV_DEFAULT_HISTFILE), ENV_ALLOC_VALUE);
	msh_env_set_if_not(msh, "HISTFILESIZE", ft_itoa(ENV_DEFAULT_HISTFILESIZE),
		ENV_ALLOC_VALUE);
	msh_env_set_if_not(msh, "HISTSIZE", ft_itoa(ENV_DEFAULT_HISTSIZE),
		ENV_ALLOC_VALUE);
	msh_env_push(msh, "IFS", ENV_DEFAULT_IFS, 0);
	msh_env_adjust_shlvl(msh, 1);
}

// ft_map_put(msh->env, _("PWD"), _("/"), &msh_env_node_free);
// ft_map_put(msh->env, _("OLDPWD"), _("/"), &msh_env_node_free);
// ft_map_put(msh->env, _("HOME"), _("/"), &msh_env_node_free);
