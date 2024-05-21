/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_defaults.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 23:15:34 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/21 23:36:47 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/env.h>
#include <ft/string/parse.h>
#include <ft/string.h>

static void	msh_env_setup_pwd(t_minishell *msh)
{
	t_variable	*v_pwd;
	t_variable	*v_home;

	v_pwd = msh_env_get(msh, "PWD", 0);
	v_home = msh_env_find(msh, "HOME");
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
	msh_env_adjust_shlvl(msh, 1);
}

// ft_map_put(msh->env, _("PWD"), _("/"), &msh_env_node_free);
// ft_map_put(msh->env, _("OLDPWD"), _("/"), &msh_env_node_free);
// ft_map_put(msh->env, _("HOME"), _("/"), &msh_env_node_free);
// ft_map_put(msh->env, _("PATH"), _("/bin:/usr/bin"), &msh_env_node_free);
