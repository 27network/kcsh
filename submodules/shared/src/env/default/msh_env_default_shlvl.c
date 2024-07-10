/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_default_shlvl.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:32:01 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/10 16:32:42 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string/parse.h>
#include <msh/env.h>

void	msh_env_adjust_shlvl(t_minishell *msh, int change)
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
