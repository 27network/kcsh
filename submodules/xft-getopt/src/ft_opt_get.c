/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opt_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 23:33:18 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/23 03:19:19 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define __FT_OPT_INTERNAL__
#include <ft/opt.h>
#include <stdio.h>

int	ft_opt_get(t_opt_globals *globals, t_opt_args *args)
{
	if (!args->posix)
	{
		//TODO: use musl's getopt_long with no long options
	}
	return (ft_opt_get_posix(globals, args));
}
