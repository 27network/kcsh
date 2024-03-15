/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 01:40:42 by kiroussa          #+#    #+#             */
/*   Updated: 2024/03/10 03:17:22 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNNER_H
# define RUNNER_H

# include <msh/minishell.h>

void	msh_run_file(t_minishell *msh, const char *filename);
int		msh_run_script(t_minishell *msh, int fd, const char *filename);
bool	msh_runner_check(t_minishell *msh, const char *file, int fd, int *ret);

#endif // RUNNER_H
