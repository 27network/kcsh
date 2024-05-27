/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:43:22 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/27 07:22:14 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H
# undef INPUT_H
# ifndef __MSH_CLI_INPUT_H__
#  define __MSH_CLI_INPUT_H__

#  include <msh/minishell.h>

char	*msh_input(t_minishell *msh, const char *interactive_prompt);
char	*msh_input_forked(t_minishell *msh, const char *interactive_prompt);

# endif // __MSH_CLI_INPUT_H__
#endif // INPUT_H
