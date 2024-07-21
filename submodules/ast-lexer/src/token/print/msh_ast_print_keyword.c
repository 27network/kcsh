/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_print_keyword.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 02:34:29 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/21 12:20:52 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/lexer.h>
#include <stdio.h>

const char	*msh_ast_strkeyword(t_ast_keyword_type type)
{
	static const char	*keyword_map[] = {
	[KW_IF] = "if", [KW_THEN] = "then", [KW_ELSE] = "else", [KW_ELIF] = "elif",
	[KW_FI] = "fi", [KW_DO] = "do", [KW_DONE] = "done", [KW_CASE] = "case",
	[KW_ESAC] = "esac", [KW_WHILE] = "while", [KW_UNTIL] = "until", [KW_FOR]
		= "for", [KW_IN] = "in", [KW_BREAK] = "break", [KW_CONTINUE]
		= "continue", [KW_RETURN] = "return", [KW_FUNCTION] = "function",
	[KW_OPEN_BRACE] = "{", [KW_CLOSE_BRACE] = "}", [KW_BANG] = "!",
	[KW_OPEN_BRACKET_BRACKET] = "[["
	};

	if (type < 0 || type >= (sizeof(keyword_map) / sizeof(*keyword_map)))
		return ("unknown");
	return (keyword_map[type]);
}

void	msh_ast_print_keyword(t_ast_token *token)
{
	if (!token)
		return ;
	printf("[%s]", msh_ast_strkeyword(token->kind));
}
