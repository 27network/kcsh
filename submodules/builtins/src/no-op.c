/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no-op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:23:00 by kiroussa          #+#    #+#             */
/*   Updated: 2024/03/25 18:58:52 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/features.h>
#include <msh/builtin/defaults.h>

/**
 * @brief no-op
 */
int	msh_builtin_no_op(int argc, char **argv)
{
	(void) argc;
	if (ft_strcmp(argv[0], "false") == 0)
		return (1);
	return (0);
}

__attribute__((constructor))
void	register_no_op(void)
{
	if (FEAT_BUILTIN_COLON)
		msh_builtin_register((t_builtin){
			.name = ":",
			.func = msh_builtin_no_op,
		});
	if (FEAT_BUILTIN_TRUE)
		msh_builtin_register((t_builtin){
			.name = "true",
			.func = msh_builtin_no_op,
		});
	if (FEAT_BUILTIN_FALSE)
		msh_builtin_register((t_builtin){
			.name = "false",
			.func = msh_builtin_no_op,
		});
}
