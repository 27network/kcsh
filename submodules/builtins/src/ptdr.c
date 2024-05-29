/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptdr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:00:54 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/30 00:04:13 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/opt.h>
#include <msh/builtin.h>
#include <msh/env.h>
#include <stdio.h>

#define PTDROPT "abc:"

int	msh_builtin_ptdr(
	int argc,
	char **argv,
	__attribute__((unused)) t_minishell *msh
) {
	t_opt_globals	opt;
	t_opt_args		args;
	int				flags[2] = {0};
	char			*cvalue = NULL;
	int				c;

	opt = ft_opt_globals();
	args = ft_opt_args(argc, argv, OPT_BASH_LIKE, PTDROPT);
	while (1)
	{
		c = ft_opt_get(&opt, &args);
		if (c == -1)
			break ;
		if (c == HELP_OPT)
			printf("HELPHELPHLEPHLEPLHP\n");
		else if (c == 'a')
			flags[0] = 1;
		else if (c == 'b')
			flags[1] = 1;
		else if (c == 'c')
			cvalue = opt.optarg;
		else
			return (1);
	}
	printf("a = %d, b = %d, c = %s\n", flags[0], flags[1], cvalue);
	for (int index = opt.optind; index < argc; index++)
		printf("Non-option argument %s\n", argv[index]);
	return (0);
}

__attribute__((constructor))
void	register_ptdr(void)
{
	msh_builtin_register((t_builtin){
		.name = "ptdr",
		.usage = "ptdr",
		.help = "ptdr",
		.func = msh_builtin_ptdr,
		.needs = NEEDS_MSH,
		.enabled = true,
		.hidden = true,
	});
}
