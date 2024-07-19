/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_node_strtype.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:13:22 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/19 14:08:20 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/builder.h>

const char	*msh_ast_node_strtype(t_ast_node_type type)
{
	static const char	*types[] = {
	[NODE_COMMAND] = "NODE_COMMAND",
	[NODE_PIPE] = "NODE_PIPE",
	[NODE_DELIM] = "NODE_DELIM",
	[NODE_GROUP] = "NODE_GROUP",
	};

	if (type < 0 || type >= (sizeof(types) / sizeof(*types)))
		return ("NODE_UNKNOWN");
	return (types[type]);
}
