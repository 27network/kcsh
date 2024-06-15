/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_is_valid_name_starter.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 12:06:39 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/15 12:07:02 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>

bool	msh_env_is_valid_name_starter(const char c)
{
	return (ft_isalpha(c) || c == '_');
}
