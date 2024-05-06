/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_tokenize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 06:40:00 by kiroussa          #+#    #+#             */
/*   Updated: 2024/03/23 03:12:37 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#define TOKENIZER_TYPES
#include <msh/ast/tokenizer.h>
#include <msh/features.h>
#include <msh/minishell.h>

/**
 * @looks for token to be merged (words)
 */
static void	msh_ast_try_merge(t_list **tokens)
{
	t_list	*current;
	t_list	*next;
	t_token	*t_curr;
	t_token	*t_next;

	current = *tokens;
	if (!current || !current->next)
		return ;
	next = current->next;
	t_curr = (t_token *) current->content;
	t_next = (t_token *) next->content;
	if (!t_curr || !t_next)
		return ;
	if (t_curr->type == TKN_WORD && t_next->type == TKN_WORD)
	{
		t_curr->data = ft_strjoin(2, "", 0b10, t_curr->data, t_next->data);
		current->next = next->next;
		ft_lst_delete(next, (t_lst_dealloc) msh_ast_tkn_free);
	}
	else
		current = current->next;
	msh_ast_try_merge(&current);
}

/**
 * @brief Tries and tokenizes a string
 */
static bool	msh_ast_try_tokenize(
		const char *line,
		size_t *cursor,
		t_list **list
) {
	char	c;
	t_token	*token;

	c = line[*cursor];
	if (c == '\\' && FEAT_PARSER_INHIBITORS)
		token = msh_ast_tokenize_escape(line, cursor);
	else if (c == '\'' || c == '\"')
		token = msh_ast_tokenize_string(line, cursor);
	else if (c == '$')
		token = msh_ast_tokenize_variable(line, cursor);
	else if (ft_strchr(SINGLE_TOKENS, c) != NULL)
		token = msh_ast_tokenize_single(line, cursor);
	else
		token = msh_ast_tokenize_word(line, cursor);
	if (!token)
		return (false);
	ft_lst_tadd(list, token);
	return (true);
}

t_list	*msh_ast_tokenize(const char *input)
{
	t_list	*list;
	size_t	cursor;
	bool	errored;
	size_t	threshold;
	size_t	loops;

	cursor = 0;
	threshold = ft_strlen(input);
	loops = 0;
	list = NULL;
	errored = false;
	while (input[cursor] != '\0' && !errored)
	{
		if (!msh_ast_try_tokenize(input, &cursor, &list))
			errored = true;
		if (input[cursor] != '\0')
			cursor++;
		if (loops++ > threshold)
			errored = true;
	}
	if (errored)
		ft_lst_free(&list, (t_lst_dealloc) msh_ast_tkn_free);
	msh_ast_try_merge(&list);
	return (list);
}
