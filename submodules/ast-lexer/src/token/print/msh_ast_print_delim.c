/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_print_delim.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 02:33:35 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/21 12:20:47 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/lexer.h>
#include <stdio.h>

const char	*msh_ast_strdelim(t_ast_delim_type type)
{
	static const char	*delim_map[] = {
	[DELIM_SEMICOLON] = ";", [DELIM_AND] = "&&", [DELIM_OR] = "||",
	[DELIM_NEWLINE] = "\\n"
	};

	if (type < 0 || type >= (sizeof(delim_map) / sizeof(*delim_map)))
		return ("unknown");
	return (delim_map[type]);
}

void	msh_ast_print_delim(t_ast_token *token)
{
	if (!token)
		return ;
	printf("[%s]", msh_ast_strdelim(token->kind));
}
