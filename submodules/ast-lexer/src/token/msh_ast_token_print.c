/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_print.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 01:11:11 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/17 23:52:07 by kiroussa         ###   ########.fr       */
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
	else if (token->type == TKN_WORD || (token->type == TKN_SUBST
			&& (token->kind == SUBST_VAR || token->kind == SUBST_VAR_RICH)))
	{
		if (!token->value.string || !*token->value.string)
			printf("[empty]");
		else
			printf("( %s )", token->value.string);
	}
	else if (token->type == TKN_DELIM)
		printf("(%s)", msh_ast_strdelim(token->kind));
}

void	msh_ast_token_print(t_minishell *msh, t_ast_token *token)
{
	if (!msh->flags.debug_tokenizer)
		return ;
	msh_ast_token_print0(token);
	printf("\n");
}
