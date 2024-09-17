/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_handle_opts.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 01:14:55 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/16 16:31:40 by emfriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	msh_handle_debug_generic(t_minishell *msh, bool generic);

static void	msh_handle_debug_opts(
	t_minishell *msh,
	const char *cmd
) {
	t_opt_handler	*debug_handlers;
	size_t			i;

	i = 0;
	debug_handlers = (t_opt_handler[]){
	{"ast", &msh->flags.debug_ast},
	{"ast-sanitizer", &msh->flags.debug_ast_sanitizer},
	{"executor", &msh->flags.debug_executor},
	{"tokenizer", &msh->flags.debug_tokenizer},
	{"token-sanitizer", &msh->flags.debug_token_sanitizer},
	{"transformer", &msh->flags.debug_transformer},
	};
	while (i < 6)
	{
		if (ft_strcmp(cmd, debug_handlers[i].name) == 0)
		{
			*(debug_handlers[i].flag) = true;
			return ;
		}
		i++;
	}
	msh_handle_invalid(msh, cmd, true);
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
		msh_handle_debug_generic(msh, true);
	else if (ft_strcmp(cmd, "--debug-almost-all") == 0)
		msh_handle_debug_generic(msh, false);
	else if (ft_strncmp(cmd, "--debug-", 8) == 0)
		msh_handle_debug_opts(msh, cmd + 8);
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
