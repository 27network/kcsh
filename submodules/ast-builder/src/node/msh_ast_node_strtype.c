/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_node_strtype.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:13:22 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/04 05:58:29 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/builder.h>

const char	*msh_ast_node_strtype(t_ast_node_type type)
{
	static const char	*types[] = {
	[NODE_COMMAND] = "COMMAND",
	[NODE_PIPE] = "PIPE",
	[NODE_DELIM] = "DELIM",
	[NODE_GROUP] = "GROUP",
	};

	if (type < 0 || type >= (sizeof(types) / sizeof(*types)))
		return ("NODE_UNKNOWN");
	return (types[type]);
}
