/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:19:22 by kiroussa          #+#    #+#             */
/*   Updated: 2024/03/19 17:04:44 by cglandus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <ft/data/list.h>
# include <ft/data/map.h>
# include <ft/io.h>
# include <ft/math.h>
# include <ft/mem.h>
# include <ft/print.h>
# include <ft/string.h>
# include <ft/string/parse.h>
# include <msh/externs.h>

# ifndef MSH_DEFAULT_NAME
#  define MSH_DEFAULT_NAME "minishell"
# endif // MSH_DEFAULT_NAME

# ifndef MSH_VERSION
#  define MSH_VERSION "0.0.0-indev"
# endif // MSH_VERSION

typedef struct s_launch_args
{
	int			argc;
	const char	**argv;
	const char	**envp;
}	t_launch_args;

typedef struct s_msh_flags
{
	bool	print_ast;
	bool	print_pipelines;
	bool	print_tokens;
}	t_msh_flags;

typedef struct s_minishell
{
	const char		*name;
	t_launch_args	launch_args;
	t_msh_flags		flags;

	t_map			*env;
	int				exit_code;
	bool			interactive;

	t_list			*free_buffer;
}	t_minishell;

int		msh_init(t_minishell *msh, int argc, char **argv, char **envp);
void	msh_destroy(t_minishell *msh);

#endif // MINISHELL_H
