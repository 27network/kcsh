/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no-op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:23:00 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/08 18:52:53 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/builtin.h>
#include <msh/features.h>

#define TRUE_HELP "Return a successful result.\n\
\n\
Exit Status:\n\
Always succeeds."

#define FALSE_HELP "Return an unsuccessful result.\n\
\n\
Exit Status:\n\
Always fails."

#define COLON_HELP "Null command.\n\
\n\
No effect; the command does nothing.\n\
\n\
Exit Status:\n\
Always succeeds."

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

[[gnu::constructor]]
void	register_no_op(void)
{
	msh_builtin_register((t_builtin){
		.name = ":",
		.usage = ":",
		.help = COLON_HELP,
		.func = msh_builtin_no_op,
		.flags = !FEAT_BUILTIN_COLON << 2 | BUILTIN_SPECIAL,
	});
	msh_builtin_register((t_builtin){
		.name = "true",
		.usage = "true",
		.help = TRUE_HELP,
		.func = msh_builtin_no_op,
		.flags = !FEAT_BUILTIN_TRUE << 2,
	});
	msh_builtin_register((t_builtin){
		.name = "false",
		.usage = "false",
		.help = FALSE_HELP,
		.func = msh_builtin_no_op,
		.flags = !FEAT_BUILTIN_FALSE << 2,
	});
}
