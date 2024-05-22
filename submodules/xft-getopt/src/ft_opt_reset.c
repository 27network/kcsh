/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opt_reset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 19:08:41 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/22 19:14:28 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/opt.h>

void	ft_opt_reset(void)
{
	static t_opt_globals	*opt = NULL;
	static bool				init = false;

	if (!init)
	{
		opt = ft_opt_globals();
		init = true;
	}
	opt->optind = 1;
	opt->optopt = 0;
	opt->optarg = NULL;
	opt->opterr = 1;
}
