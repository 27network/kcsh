/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 01:40:42 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/18 01:03:48 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNNER_H
# define RUNNER_H
# undef RUNNER_H
# ifndef __MSH_CLI_RUNNER_H__
#  define __MSH_CLI_RUNNER_H__

#  include <msh/minishell.h>

bool	msh_runner_check(t_minishell *msh, const char *file, int fd, int *ret);
void	msh_run_file(t_minishell *msh, const char *filename, int argc,
			const char **argv);
void	msh_run_setup_script(t_minishell *msh, int fd, const char *filename);

# endif // __MSH_CLI_RUNNER_H__
#endif // RUNNER_H
