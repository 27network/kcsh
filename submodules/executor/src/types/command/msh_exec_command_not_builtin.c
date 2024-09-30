/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_command_not_builtin.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 04:25:04 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/30 04:25:10 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/data/list.h>
#include <msh/builtin.h>
#include <msh/exec.h>

bool	msh_exec_command_not_builtin(t_ast_node *node)
{
	t_ast_token		*tkn;
	char			*cmd;
	t_builtin		*builtin;

	if (ft_lst_size(node->command.args) == 0)
		return (true);
	tkn = (t_ast_token *) node->command.args->content;
	cmd = NULL;
	if (tkn && tkn->value.string)
		cmd = tkn->value.string;
	if (!cmd)
		return (true);
	builtin = msh_builtin_get(cmd);
	return (!builtin || builtin->flags & BUILTIN_DISABLED);
}
