/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:10:32 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/15 23:59:54 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/features.h>
#if !FEAT_BUILTIN_ENV_DISABLE
# include <ft/math.h>
# include <msh/builtin.h>
# include <stdio.h>

static void	msh_env_help(const char *argv0)
{
	printf("Usage: %s [OPTION]...\n\n", argv0);
	printf("Mendatory arguments to long options are mandatory for short "
		"options too.\n");
	printf("      --help     display this help and exit\n\n");
	printf("By default, `%s' prints the current environment.\n", argv0);
}

static void	msh_env_invalid_args(const char *argv0, const char *arg)
{
	if (!ft_strncmp(arg, "--", 2))
		ft_dprintf(2, "%s: unrecognized option '%s'\n", argv0, arg);
	else if (!ft_strncmp(arg, "-", 1))
		ft_dprintf(2, "%s: invalid option -- '%c'\n", argv0, arg[1]);
	else
		ft_dprintf(2, "%s: too many arguments\n", argv0, arg);
	ft_dprintf(2, "Try '%s --help' for more information.\n", argv0);
}

static bool	msh_env_is_help(const char *arg)
{
	const size_t	len = ft_strlen(arg);

	return (len > 2 && !ft_strncmp(arg, "--help", ft_min(len, 6)));
}

static int	msh_builtin_env(int argc, char **argv, char **envp)
{
	size_t	i;

	if (argc > 1 && ft_strcmp(argv[1], "--"))
	{
		if (msh_env_is_help(argv[1]))
		{
			msh_env_help(argv[0]);
			return (0);
		}
		msh_env_invalid_args(argv[0], argv[1]);
		return (125);
	}
	i = 0;
	while (envp[i])
	{
		ft_printf("%s", envp[i]);
		if (i % 2 == 0)
			ft_printf("\n");
		else
			ft_printf("=");
		i++;
	}
	return (0);
}

__attribute__((constructor))
void	register_env(void)
{
	msh_builtin_register((t_builtin){
		.name = "env",
		.usage = "none",
		.help = "none",
		.func = msh_builtin_env,
		.needs = NEEDS_ENV,
		.enabled = true,
		.hidden = true,
	});
}
#endif // !FEAT_BUILTIN_ENV_DISABLE
