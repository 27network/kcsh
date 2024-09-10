/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_opt_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 01:15:09 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/09 01:51:15 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <ft/print.h>
#include <msh/cli/opt.h>
#include <msh/cli/shell.h>
#include <msh/exec.h>

static int	msh_find_flag_index(const char **argv)
{
	int		i;
	size_t	length;

	i = 0;
	while (argv[i])
	{
		length = ft_strlen(argv[i]);
		if (argv[i][0] == '-' && argv[i][length - 1] == 'c')
			return (i);
		i++;
	}
	return (-1);
}

void	msh_opt_command(t_minishell *msh, int argc, const char **argv)
{
	char	*cmd;
	int		c_flag_index;

	c_flag_index = msh_find_flag_index(argv);
	if (c_flag_index == -1 || argc <= c_flag_index + 1)
		msh_error(msh, "-c: option requires an argument\n");
	if (c_flag_index == -1 || argc <= c_flag_index + 1)
		msh_exit(msh, 2);
	cmd = (char *) argv[c_flag_index + 1];
	if (argc > c_flag_index + 2)
		msh->name = argv[c_flag_index + 2];
	if (msh->name == NULL)
		msh->name = MSH_DEFAULT_NAME;
	msh->interactive = false;
	msh->execution_context.show_line = true;
	msh->execution_context.line = 1;
	cmd = (char *) ft_strdup(cmd);
	if (!cmd)
		msh_error(msh, "-c: %s\n", "error while allocating memory");
	if (!cmd)
		msh_exit(msh, 1);
	msh_shell_handle_input(msh,
		(t_input_result){.buffer = cmd, .type = INPUT_EOF});
	msh_exit(msh, msh->execution_context.exit_code);
}
