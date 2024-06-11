/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_is_valid_name.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 22:13:45 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/10 22:38:28 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/env.h>

static bool	msh_env_is_valid_name_char(char c)
{
	return (ft_isalnum(c));
}

bool	msh_env_is_valid_name(const char *name, uint64_t context)
{
	if (!name || !*name)
		return (false);
	if (!msh_env_is_valid_name_starter(*name, context))
		return (false);
	if (msh_env_is_special_name(name, context))
		return (true);
	name++;
	while (*name)
	{
		if (!msh_env_is_valid_name_char(*name))
			return (false);
		name++;
	}
	return (true);
}
