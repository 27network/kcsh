/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_tokenize_post.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 06:46:27 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/04 22:26:52 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/data/list.h>
#include <ft/string.h>
#include <msh/ast/lexer.h>

static t_list	*msh_find_effective_next(t_list *lst)
{
	t_list		*next;
	t_ast_token	*tkn;

	if (!lst)
		return (NULL);
	next = lst->next;
	if (!next)
		return (NULL);
	tkn = (t_ast_token *) next->content;
	if (!tkn)
		return (NULL);
	if (tkn->type == TKN_SEP)
		return (msh_find_effective_next(next));
	return (next);
}

static void	msh_ast_tokenize_post_check_semicolon(t_ast_lexer *state,
						t_list *current)
{
	t_list		*effective_next;
	t_ast_token	*tkn;

	effective_next = msh_find_effective_next(current);
	if (effective_next)
	{
		tkn = (t_ast_token *) effective_next->content;
		if (tkn->type == TKN_DELIM && tkn->kind == DELIM_NEWLINE)
			ft_lst_remove(&state->tokens, effective_next,
				(t_lst_dealloc) msh_ast_token_free);
	}
}

void	msh_ast_tokenize_post(t_ast_lexer *state,
				__attribute__((unused)) t_ast_token *token,
				t_ast_error *err)
{
	t_list		*current;
	t_ast_token	*tkn;

	if (err->type != AST_ERROR_NONE)
		return ;
	if (!ft_strstr("})", state->delim))
		return ;
	current = state->tokens;
	while (current)
	{
		if (current != state->tokens && current != ft_lst_last(state->tokens))
		{
			tkn = (t_ast_token *) current->content;
			if (tkn->type == TKN_DELIM && tkn->kind == DELIM_SEMICOLON)
				msh_ast_tokenize_post_check_semicolon(state, current);
			else if (tkn->type == TKN_DELIM && tkn->kind == DELIM_NEWLINE)
				tkn->kind = DELIM_SEMICOLON;
		}
		current = current->next;
	}
}
