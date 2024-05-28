/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:43:22 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/27 16:00:59 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H
# undef INPUT_H
# ifndef __MSH_CLI_INPUT_H__
#  define __MSH_CLI_INPUT_H__

#  include <msh/minishell.h>

typedef enum e_input_result
{
	INPUT_OK = 0,
	INPUT_EOF,
	INPUT_INTERRUPTED,
	INPUT_ERROR,
}	t_input_result_type;

typedef struct s_input_result
{
	t_input_result_type	type;
	char				*buffer;
}	t_input_result;

t_input_result	msh_input(t_minishell *msh,
					const char *interactive_prompt);
t_input_result	msh_input_forked(t_minishell *msh,
					const char *interactive_prompt);

# endif // __MSH_CLI_INPUT_H__
#endif // INPUT_H
