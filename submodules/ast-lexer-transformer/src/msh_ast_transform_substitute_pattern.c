/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_transform_substitute_pattern.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 07:40:33 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/09 02:34:43 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <msh/ast/transformer.h>
#include <msh/env.h>
#include <msh/log.h>
#include <stdio.h>

#define LEVEL MSG_DEBUG_EXEC_TRANSFORMER

static t_ast_error	msh_ast_pattern_fill_lists(t_list **lists, t_list **tokens)
{
	size_t		n;
	t_list		*current;
	t_ast_token	*token;

	n = 0;
	current = *tokens;
	while (current)
	{
		token = (t_ast_token *)current->content;
		if (token->type == TKN_SEP)
		{
			current->content = NULL;
			msh_ast_token_free(token);
			n++;
		}
		else if (ft_lst_tadd(lists + n, token) == NULL)
			break ;
		current = current->next;
	}
	return (msh_ast_ok());
}

t_ast_error	msh_ast_transform_run_pattern_matching(t_minishell *msh,
						t_list **tokens);

static t_ast_error	msh_ast_transform_run_patterns(t_minishell *msh,
				t_list **lists, size_t size)
{
	size_t		i;
	t_ast_error	err;

	err = msh_ast_ok();
	i = 0;
	while (i < size)
	{
		err = msh_ast_transform_run_pattern_matching(msh, lists + i);
		i++;
	}
	return (err);
}

static t_ast_error	msh_ast_transform_join_lists(
	__attribute__((unused)) t_minishell *msh,
				t_list **lists, t_list **tokens)
{
	t_list		*current;
	t_list		*buffer;
	t_list		*target;
	t_ast_token	*token;

	target = NULL;
	while (*lists)
	{
		current = *lists;
		lists++;
		while (current)
		{
			buffer = current;
			current = current->next;
			buffer->next = NULL;
			ft_lst_add(&target, buffer);
		}
		if (*lists && msh_ast_token_new(TKN_SEP, &token).type != AST_ERROR_NONE)
			return (msh_ast_errd(AST_ERROR_ALLOC, "failed to allocate "
					"token for separator", false));
		if (*lists && token)
			ft_lst_tadd(&target, token);
	}
	*tokens = target;
	return (msh_ast_ok());
}

static void	msh_ast_free_pattern_lists(t_list **lists, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		ft_lst_free(&lists[i++], NULL);
	free(lists);
	*lists = NULL;
}

t_ast_error	msh_ast_transform_substitute_pattern(t_minishell *msh,
				t_list **tokens, __attribute__((unused)) size_t order)
{
	size_t		sep;
	t_list		**lists;
	t_ast_error	err;

	if (!tokens || !*tokens || !msh_ast_token_rcount(*tokens, TKN_SUBST))
		return (msh_ast_ok());
	sep = msh_ast_token_count(*tokens, TKN_SEP);
	lists = ft_calloc(sep + 2, sizeof(t_list *));
	if (!lists)
		return (msh_ast_errd(AST_ERROR_ALLOC, "failed to allocate "
				"pattern subst lists", false));
	err = msh_ast_pattern_fill_lists(lists, tokens);
	if (!err.type)
		err = msh_ast_transform_run_patterns(msh, lists, sep + 1);
	if (err.type)
		msh_ast_free_pattern_lists(lists, sep + 1);
	else
	{
		ft_lst_free(tokens, NULL);
		err = msh_ast_transform_join_lists(msh, lists, tokens);
		free(lists);
	}
	return (err);
}
