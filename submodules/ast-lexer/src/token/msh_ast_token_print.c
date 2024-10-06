/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_print.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 01:11:11 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/07 00:45:47 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/lexer/tokens.h>
#include <msh/ast/lexer/kinds.h>
#include <msh/minishell.h>
#include <stdio.h>

void	msh_ast_print_delim(t_ast_token *token);
void	msh_ast_print_group(t_ast_token *token);
void	msh_ast_print_keyword(t_ast_token *token);
void	msh_ast_print_redir(t_ast_token *token);
void	msh_ast_print_string(t_ast_token *token);

void	msh_ast_token_print0(t_ast_token *token)
{
	if (!token)
		return ;
	printf("%s", msh_ast_strtoken(token->type));
	if (token->type == TKN_KEYWORD)
		msh_ast_print_keyword(token);
	else if (token->type == TKN_STRING || token->type == TKN_GROUP)
		msh_ast_print_group(token);
	else if (token->type == TKN_REDIR)
		msh_ast_print_redir(token);
	else if (token->type == TKN_WORD || token->type == TKN_NUMBER
		|| (token->type == TKN_SUBST && (token->kind == SUBST_VAR
				|| token->kind == SUBST_VAR_RICH || token->kind == SUBST_TILDE
				|| token->kind == SUBST_PATTERN)))
		msh_ast_print_string(token);
	else if (token->type == TKN_DELIM)
		msh_ast_print_delim(token);
}

void	msh_ast_token_print(t_minishell *msh, t_ast_token *token)
{
	if (msh && !msh->flags.debug_tokenizer)
		return ;
	msh_ast_token_print0(token);
	printf("\n");
}
