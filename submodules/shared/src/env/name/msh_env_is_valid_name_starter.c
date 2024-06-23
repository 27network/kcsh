/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_is_valid_name_starter.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 12:06:39 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/23 01:49:35 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <stdbool.h>

bool	msh_env_is_valid_name_starter(const char c)
{
	return (ft_isalpha(c) || c == '_');
}
