/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:10:32 by kiroussa          #+#    #+#             */
/*   Updated: 2024/04/02 01:07:59 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/features.h>
#if !FEAT_BUILTIN_ENV_DISABLE
# include <msh/builtin/defaults.h>

static void	msh_env_help(const char *argv0)
{
	printf("Usage: %s [OPTION]...\n\n", argv0);
	printf("Mendatory arguments to long options are mandatory for short "
		"options too.\n");
	printf("      --help     display this help and exit\n");
	printf("      --version  output version information and exit\n\n");
	printf("By default, `%s' prints the current environment.\n", argv0);
}

static int	msh_builtin_env(int argc, char **argv, char **envp)
{
	int	nl;

	nl = 0;
	if (argc == 2 && !ft_strcmp(argv[1], "--help"))
	{
		msh_env_help(argv[0]);
		return (0);
	}
	while (*envp)
	{
		ft_printf("%s", *envp);
		if (nl)
			ft_printf("\n");
		else
			ft_printf("=");
		nl ^= 1;
		envp++;
	}
	return (0);
}

__attribute__((constructor))
void	register_env(void)
{
	msh_builtin_register((t_builtin){
		.name = "env",
		.func = msh_builtin_env,
		.needs = NEEDS_ENV,
	});
}
#endif // !FEAT_BUILTIN_ENV_DISABLE
