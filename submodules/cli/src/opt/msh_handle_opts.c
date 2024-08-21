/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_handle_opts.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 01:14:55 by kiroussa          #+#    #+#             */
/*   Updated: 2024/08/21 15:00:21 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define AVAILABLE_SHORT_OPTS "c"

#include <ft/string.h>
#include <ft/print.h>
#include <msh/cli/runner.h>
#define MSH_OPT_IMPL
#include <msh/cli/opt.h>

void	msh_print_help(t_minishell *msh, int fd);

static void	msh_handle_invalid(t_minishell *msh, const char *flag, bool is_long)
{
	if (is_long)
		msh_error(msh, "%s: %s\n", flag, "invalid option");
	else
		msh_error(msh, "-%c: %s\n", flag[0], "invalid option");
	msh_print_help(msh, 2);
	msh_exit(msh, 2);
}

static void	msh_handle_short(
	t_minishell *msh,
	const char *cmds,
	int argc,
	const char **argv
) {
	size_t	i;
	bool	valid;

	valid = true;
	i = 0;
	while (cmds[i])
	{
		if (cmds[i] == 'c')
			msh_opt_command(msh, argc, argv);
		else
			valid = false;
		i++;
	}
	if (!valid)
		msh_handle_invalid(msh, cmds, false);
}

static void	msh_handle_debug_generic(t_minishell *msh)
{
	msh->flags.debug_generic = true;
	msh->flags.debug_ast = true;
	msh->flags.debug_executor = true;
	msh->flags.debug_pipelines = true;
	msh->flags.debug_sanitizer = true;
	msh->flags.debug_tokenizer = true;
	msh->flags.debug_transformer = true;
}

static void	msh_handle_opt(
	t_minishell *msh,
	const char *cmd,
	int argc,
	const char **argv
) {
	if (ft_strcmp(cmd, "--version") == 0)
		msh_opt_version(msh);
	else if (ft_strcmp(cmd, "--flags") == 0)
		msh_opt_flags(msh);
	else if (ft_strcmp(cmd, "--debug") == 0)
		msh_handle_debug_generic(msh);
	else if (ft_strcmp(cmd, "--debug-ast") == 0)
		msh->flags.debug_ast = true;
	else if (ft_strcmp(cmd, "--debug-executor") == 0)
		msh->flags.debug_executor = true;
	else if (ft_strcmp(cmd, "--debug-pipelines") == 0)
		msh->flags.debug_pipelines = true;
	else if (ft_strcmp(cmd, "--debug-sanitizer") == 0)
		msh->flags.debug_sanitizer = true;
	else if (ft_strcmp(cmd, "--debug-tokenizer") == 0)
		msh->flags.debug_tokenizer = true;
	else if (ft_strcmp(cmd, "--debug-transformer") == 0)
		msh->flags.debug_transformer = true;
	else if (ft_strncmp(cmd, "--", 2) == 0)
		msh_handle_invalid(msh, cmd, true);
	else if (ft_strncmp(cmd, "-", 1) == 0)
		msh_handle_short(msh, cmd + 1, argc, argv);
	else
		msh_run_file(msh, cmd, argc, argv);
}

void	msh_handle_opts(t_minishell *msh, int argc, const char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "--help") == 0)
			msh_opt_help(msh);
		i++;
	}
	i = 1;
	while (i < argc)
	{
		msh_handle_opt(msh, argv[i], argc, argv);
		i++;
	}
}
