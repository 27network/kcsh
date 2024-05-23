/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opt_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 19:16:17 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/22 20:43:20 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/opt.h>

t_opt_args	ft_opt_args(int argc, char **argv, bool posix,
					const char *optstring)
{
	return ((t_opt_args){argc, argv, posix, optstring});
}
