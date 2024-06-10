/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_print.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 01:11:11 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/03 21:05:33 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define __DUMB_LIBFT_FIX
#include <msh/ast/lexer/tokens.h>
#include <msh/ast/lexer/kinds.h>
#include <msh/minishell.h>
#include <stdio.h>

static void	msh_ast_token_print0(t_ast_token *token);

static void	msh_ast_token_print_list(t_ast_token *token)
{
	msh_ast_token_print0(token);
	printf(" ");
}

static const char	*msh_ast_strkeyword(t_ast_keyword_type type)
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

static void	msh_ast_token_print0(t_ast_token *token)
{
	const char	*type = msh_ast_strtoken(token->type);

	printf("%s", type);
	if (token->type == TKN_KEYWORD)
		printf("[%s]", msh_ast_strkeyword(token->kind));
	else if (token->type == TKN_STRING || token->type == TKN_GROUP)
	{
		printf("( ");
		ft_lst_foreach(token->value.list,
			(t_list_foreach_fn *) msh_ast_token_print_list);
		printf(")");
	}
	else if (token->type == TKN_WORD)
	{
		if (!token->value.string || !*token->value.string)
			printf("[empty]");
		else
			printf("( %s )", token->value.string);
	}
}

void	msh_ast_token_print(t_minishell *msh, t_ast_token *token)
{
	if (!msh->flags.debug_tokenizer)
		return ;
	msh_ast_token_print0(token);
	printf("\n");
}
