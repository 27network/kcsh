/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 01:15:43 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/11 23:11:17 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPT_H
# define OPT_H
# undef OPT_H
# ifndef __MSH_CLI_OPT_H__
#  define __MSH_CLI_OPT_H__

#  include <msh/log.h>
#  include <msh/minishell.h>

#  define RETURN_SUCCESS 0
#  define RETURN_INVALID_OPT 2

typedef struct s_opt_handler
{
	const char	*name;
	bool		*flag;
}	t_opt_handler;

void	msh_handle_opts(t_minishell *msh, int argc, const char **argv);

#  ifdef MSH_OPT_IMPL

void	msh_opt_command(t_minishell *msh, int argc, const char **argv);
void	msh_opt_help(t_minishell *msh);
void	msh_opt_version(t_minishell *msh);
void	msh_opt_flags(t_minishell *msh);

#  endif // MSH_OPT_IMPL

# endif // __MSH_CLI_OPT_H__
#endif // OPT_H
