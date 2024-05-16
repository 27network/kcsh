/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_opt_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 00:01:29 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/16 01:46:30 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <ft/string.h>
#include <msh/features.h>
#include <msh/cli/opt.h>
#include <stdio.h>

void	msh_print_version(int fd);

void	msh_opt_flags(t_minishell *msh)
{
	char	*flags;
	size_t	i;

	flags = ENABLED_FEATURES_STRING;
	msh_print_version(1);
	if (ft_strlen(flags) == 0)
		ft_putendl("No feature flags enabled\n");
	else
	{
		ft_putstr("Enabled feature flags:\n- ");
		i = 0;
		while (flags[i])
		{
			ft_putstr(flags + i);
			i += ft_strlen(flags + i) + 1;
			if (ft_strlen(flags + i) != 0)
				ft_putstr(" ");
		}
		ft_putchar('\n');
	}
	msh_exit(msh, 0);
}
