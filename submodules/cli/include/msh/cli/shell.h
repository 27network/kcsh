/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 05:19:05 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/18 02:38:52 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# undef SHELL_H
# ifndef __MSH_SHELL_H__
#  define __MSH_SHELL_H__

#  include <msh/minishell.h>

void	msh_shell_loop(t_minishell *msh);

char	*msh_prompt_bash(t_minishell *msh);
void	msh_handle_line(t_minishell *msh, char *line);

# endif // __MSH_SHELL_H__
#endif // SHELL_H
