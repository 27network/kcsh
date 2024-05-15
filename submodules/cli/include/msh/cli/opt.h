/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 01:15:43 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/15 23:21:43 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPT_H
# define OPT_H
# undef OPT_H
# ifndef __MSH_CLI_OPT_H__
#  define __MSH_CLI_OPT_H__

#  include <msh/minishell.h>

#  define RETURN_SUCCESS 0
#  define RETURN_INVALID_OPT 2

void	msh_handle_opts(t_minishell *msh, int argc, const char **argv);

#  ifdef MSH_OPT_IMPL

void	msh_opt_command(t_minishell *msh, int argc, const char **argv);
void	msh_opt_help(t_minishell *msh);
void	msh_opt_version(t_minishell *msh);

#  endif // MSH_OPT_IMPL

# endif // __MSH_CLI_OPT_H__
#endif // OPT_H
