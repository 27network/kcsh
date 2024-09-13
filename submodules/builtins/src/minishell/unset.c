/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouchet <ebouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:11:19 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/10 18:00:21 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/builtin.h>
#include <msh/env.h>

#if FEAT_BUILTIN_UNSET_OPT
# define UNSET_USAGE "unset [-f] [-v] [-n] [name ...]"
# define UNSET_HELP ""
# define VALID_OPTIONS ""
#else
# define UNSET_USAGE "unset [name ...]"
# define UNSET_HELP ""
# define VALID_OPTIONS ""
#endif // FEAT_BUILTIN_UNSET_OPT

static int	msh_builtin_unset(
	__attribute__((unused)) int argc,
	char **argv,
	t_minishell *msh
) {
	int			i;
	t_variable	*variable;
	int			ret;

	i = 0;
	ret = 0;
	while (argv[++i])
	{
		if (msh_env_is_valid_name(argv[i], true))
		{
			variable = msh_env_find(msh, argv[i]);
			if (!variable)
				continue ;
			if (!(variable->flags & ENV_READONLY))
				msh_env_remove(msh, argv[i]);
			else
			{
				msh_error(msh, "unset: %s: cannot unset: "
					"readonly variable\n", argv[i]);
				ret = 1;
			}
		}
	}
	return (ret);
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
