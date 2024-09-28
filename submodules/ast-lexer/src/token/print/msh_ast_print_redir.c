/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_print_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:53:37 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/28 14:06:58 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/data/list.h>
#include <msh/ast/lexer.h>
#include <stdio.h>

const char	*msh_ast_strredir(t_ast_redir_type type)
{
	static const char	*redir_strs[] = {
	[REDIR_FILE_IN] = "<", [REDIR_FILE_OUT] = ">", [REDIR_FILE_CLOBBER] = ">|",
	[REDIR_FILE_INOUT] = "<>", [REDIR_FILE_APPEND] = ">>", [REDIR_FD_IN] = "<&",
	[REDIR_FD_OUT] = ">&", [REDIR_HEREDOC] = "<<", [REDIR_HEREDOC_STRIP]
		= "<<-", [REDIR_HERESTRING] = "<<<", [REDIR_FILE_CLOBBER_A] = "&>|",
	[REDIR_FILE_OUT_A] = "&>"
	};

	if (type < 0 || type > REDIR_FILE_OUT)
		return ("unknown");
	return (redir_strs[type]);
}

void	msh_ast_token_print_list(void *token);

void	msh_ast_print_redir(t_ast_token *token)
{
	if (!token)
		return ;
	printf("( ");
	printf("%d", token->value.redir.left_fd);
	printf(" %s ", msh_ast_strredir(token->kind));
	if (token->kind == REDIR_FD_IN || token->kind == REDIR_FD_OUT)
		printf("&%d", token->value.redir.right_fd);
	else if (token->value.redir.state == REDIR_STATE_WORD)
		ft_lst_foreach(token->value.redir.right_word, msh_ast_token_print_list);
	else
		printf("[missing]");
	printf(" )");
}
