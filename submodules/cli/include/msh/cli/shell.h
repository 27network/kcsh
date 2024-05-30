/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 05:19:05 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/30 18:52:24 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# undef SHELL_H
# ifndef __MSH_SHELL_H__
#  define __MSH_SHELL_H__

#  include <msh/minishell.h>
#  include <msh/cli/input.h>

void	msh_shell_loop(t_minishell *msh);
void	msh_shell_handle_input(t_minishell *msh, t_input_result input);

char	*msh_shell_prompt_parse(t_minishell *msh);

t_list	*msh_ast_lex(t_minishell *msh, t_input_result input, char *prompt);

# endif // __MSH_SHELL_H__
#endif // SHELL_H
