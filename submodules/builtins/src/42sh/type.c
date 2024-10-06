/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 05:16:18 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/04 06:24:36 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/builtin.h>
#include <msh/env.h>
#include <msh/features.h>
#include <msh/log.h>
#include <msh/util.h>

#define TYPE_USAGE "type name [name ...]"
#define TYPE_HELP "Display information about command type.\n\
\n\
For each NAME, indicate how it would be interpreted if used as a\n\
command name.\n\
\n\
Arguments:\n\
  NAME      Command name to be interpreted.\n\
\n\
Exit Status:\n\
Returns success if all of the NAMEs are found; fails if any are not found."

//TODO(42sh): add aliases detection (%s is aliased to `%s')
static int	msh_try_find_type(t_minishell *msh, const char *name)
{
	t_builtin	*builtin;
	const char	*path;

	builtin = msh_builtin_get(name);
	if (builtin && !(builtin->flags & BUILTIN_DISABLED)
		&& !(builtin->flags & BUILTIN_HIDDEN))
	{
		ft_printf("%s is a shell builtin\n", name);
		return (0);
	}
	path = msh_resolve_path(msh, name);
	if (path)
	{
		ft_printf("%s is %s\n", name, path);
		return (0);
	}
	msh_error(msh, "type: %s: not found\n", name);
	return (1);
}

static int	msh_builtin_type(int argc, char **argv, t_minishell *msh)
{
	int		ret;

	ret = 0;
	if (argc > 1)
	{
		while (argv[1])
		{
			if (msh_try_find_type(msh, argv[1]))
				ret = 1;
			argv++;
		}
	}
	return (ret);
}

__attribute__((constructor))
void	register_type(void)
{
	msh_builtin_register((t_builtin){
		.name = "type",
		.usage = TYPE_USAGE,
		.help = TYPE_HELP,
		.func = msh_builtin_type,
		.flags = !FEAT_BUILTIN_SET << 2 | BUILTIN_NEEDS_MSH,
	});
}
