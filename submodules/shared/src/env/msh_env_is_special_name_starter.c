/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_is_special_name_starter.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 11:59:27 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/15 12:05:38 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/features.h>

#define SPECIAL_VARS "*@#?-$!"

bool	msh_env_is_special_name_starter(const char c)
{
	if (FEAT_SCRIPTING)
	{
		if (ft_strchr(SPECIAL_VARS, c))
			return (true);
	}
	return (c == '?');
}
