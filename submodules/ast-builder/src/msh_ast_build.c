/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_build.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:17:03 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/03 22:20:07 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <msh/ast/builder.h>
#include <msh/log.h>
#include <msh/util.h>

const char	*msh_syntax_error(t_ast_token *token);
t_ast_error	msh_ast_build(t_minishell *msh, t_list *tokens,
				t_ast_node **result);

static t_list	*msh_ast_find_tkn(t_minishell *msh, t_list *tokens,
					t_ast_token_type type)
{
	t_list		*node;
	t_list		*last;
	t_ast_token	*tok;

	(void) msh;
	node = tokens;
	last = NULL;
	while (node)
	{
		tok = (t_ast_token *) node->content;
		if (tok)
		{
			if (tok->type == type)
				last = node;
		}
		node = node->next;
	}
	msh_log(msh, MSG_DEBUG_AST_BUILDER, "split on %s? %s\n",
		msh_ast_strtoken(type), msh_strbool(!!last));
	return (last);
}

#define EOF_WOMP_WOMP "Unexpected end of input"

static t_ast_error	msh_ast_root_node(t_minishell *msh, t_list *tokens,
						t_list *sep, t_ast_node **result)
{
	if (!sep)
		return (msh_ast_node_command(msh, tokens, result));
	if (!sep->next)
		return (msh_ast_errd(AST_ERROR_UNEXPECTED, EOF_WOMP_WOMP, true));
	if (sep == tokens)
		return (msh_ast_errd(AST_ERROR_SYNTAX, (void *) msh_syntax_error(
					(t_ast_token *) sep->content), false));
	return (msh_ast_node_sep(msh, tokens, sep, result));
}

#undef EOF_WOMP_WOMP

#define NO_TOKENS_MSG "No tokens to define an AST with... what?"

t_ast_error	msh_ast_build(t_minishell *msh, t_list *tokens, t_ast_node **result)
{
	t_list		*split_node;
	t_ast_error	err;

	if (!tokens)
		return (msh_ast_errd(AST_ERROR_ALLOC, NO_TOKENS_MSG, false));
	split_node = msh_ast_find_tkn(msh, tokens, TKN_DELIM);
	if (!split_node)
		split_node = msh_ast_find_tkn(msh, tokens, TKN_PIPE);
	if (!split_node)
		split_node = msh_ast_find_tkn(msh, tokens, TKN_GROUP);
	err = msh_ast_root_node(msh, tokens, split_node, result);
	if (err.type)
		msh_log(msh, MSG_DEBUG_AST_BUILDER, "error: ");
	if (err.type && msh->flags.debug_ast)
		msh_ast_error_print(msh, err);
	return (err);
}
