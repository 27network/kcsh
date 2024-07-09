/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouchet <ebouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:11:19 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/09 13:25:50 by ebouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/builtin.h>
#include <msh/env.h>
#include <stdio.h>
#include <ft/mem.h>

#define UNSET_USAGE ""
#define UNSET_HELP ""

static int	msh_builtin_unset(int argc, char **argv, t_minishell *msh)
{
	int			i;
	t_variable	*value;

	i = 1;
	while (argv[i])
	{
		if (msh_env_is_valid_name(argv[i], true))
		{
			value = msh_env_find(msh, argv[i]);
			if (value)
				msh_env_remove(msh, argv[i]);
		}
		i++;
	}
	return (0);
}

__attribute__((constructor))
void	register_unset(void)
{
	msh_builtin_register((t_builtin){
		.name = "unset",
		.usage = UNSET_USAGE,
		.help = UNSET_HELP,
		.func = msh_builtin_unset,
		.flags = BUILTIN_NEEDS_MSH | BUILTIN_SPECIAL,
	});
}