/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 00:49:32 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/22 13:14:59 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/features.h>
#if FEAT_BUILTIN_SET
# include <msh/builtin.h>
# include <msh/env.h>

static void	msh_print_vars(t_minishell *msh)
{
	t_variable	*root;
	t_variable	*tmp;

	root = msh_env_sorted(msh);
	if (!root)
		msh_error(msh, "msh_print_vars: msh_env_sorted failed\n");
	if (!root)
		return ;
	while (root)
	{
		if (root->value && !(root->flags & ENV_INVISIBLE))
			msh_env_print_assignment(msh, root, 0);
		tmp = root;
		root = root->next;
		msh_env_free(tmp);
	}
}

static int	msh_builtin_set(int argc, char **argv, t_minishell *msh)
{
	if (argc == 1 || !FEAT_BUILTIN_SET_FULL)
		msh_print_vars(msh);
	if (!FEAT_BUILTIN_SET_FULL)
		return (0);
	(void) argv;
	return (0);
}

__attribute__((constructor))
void	register_set(void)
{
	msh_builtin_register((t_builtin){
		.name = "set",
		.usage = NULL,
		.help = NULL,
		.func = msh_builtin_set,
		.needs = NEEDS_MSH,
		.enabled = true,
	});
}
#endif // FEAT_BUILTIN_SET
