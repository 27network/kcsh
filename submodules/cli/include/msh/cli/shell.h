/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 05:19:05 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/22 16:02:31 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# undef SHELL_H
# ifndef __MSH_SHELL_H__
#  define __MSH_SHELL_H__

#  include <ft/data/list.h>
#  include <msh/ast/types.h>
#  include <msh/cli/input.h>

void	msh_shell_loop(t_minishell *msh);
void	msh_shell_handle_input(t_minishell *msh, t_input_result input);

char	*msh_shell_prompt_parse(t_minishell *msh);

bool	msh_ast_lex(t_minishell *msh, t_input_result input, char *prompt,
			t_list **result);
bool	msh_ast_create(t_minishell *msh, t_list *tokens, t_ast_node **result);
void	msh_dump_tokens(t_minishell *msh, t_list *tokens);

bool	msh_exec_wrap(t_minishell *msh, t_ast_node *ast);

# endif // __MSH_SHELL_H__
#endif // SHELL_H
