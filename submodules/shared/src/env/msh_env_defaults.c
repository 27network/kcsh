/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_defaults.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 23:15:34 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/21 13:09:01 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/env.h>
#include <ft/string/parse.h>
#include <ft/string.h>

static void	msh_env_setup_pwd(t_minishell *msh)
{
	t_variable	*v_pwd;
	t_variable	*v_home;

	v_pwd = msh_env_get_create(msh, "PWD");
	v_home = msh_env_get(msh, "HOME");
	// if (v_home && v_pwd &&
	msh_env_set_flag(v_pwd, ENV_EXPORTED);
}

static void	msh_env_adjust_shlvl(t_minishell *msh, int change)
{
	char		*old_shlvl;
	int			shlvl;
	t_variable	*v_shlvl;

	old_shlvl = msh_env_get_string(msh, "SHLVL");
	if (!old_shlvl)
		old_shlvl = "0";
	shlvl = ft_atoi(old_shlvl);
	shlvl += change;
	if (shlvl < 0)
		shlvl = 0;
	else if (shlvl >= 1000)
		shlvl = 1;
	v_shlvl = msh_env_get(msh, "SHLVL");
	msh_env_set_string(v_shlvl, ft_itoa(shlvl));
	msh_env_set_flag(v_shlvl, ENV_ALLOC_VALUE | ENV_EXPORTED);
}

void	msh_env_defaults(t_minishell *msh)
{
	msh_env_setup_pwd(msh);
	msh_env_adjust_shlvl(msh, 1);
}

// ft_map_put(msh->env, _("PWD"), _("/"), &msh_env_node_free);
// ft_map_put(msh->env, _("OLDPWD"), _("/"), &msh_env_node_free);
// ft_map_put(msh->env, _("HOME"), _("/"), &msh_env_node_free);
// ft_map_put(msh->env, _("PATH"), _("/bin:/usr/bin"), &msh_env_node_free);
