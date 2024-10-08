/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_sanitize_token_word_before.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:13:03 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/08 21:23:55 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#define MSH_SANITIZER_TYPE t_list
#include <msh/ast/sanitizer.h>
#include <msh/log.h>
#include <msh/util.h>

const char	*msh_syntax_error_impl(t_ast_token *token, const char *paren);
const char	*msh_syntax_error(t_ast_token *token);

static t_ast_error	msh_ast_sanitize_token_check_prev(
	__attribute__((unused)) t_minishell *msh,
	__attribute__((unused)) t_list *current,
	t_ast_token *token,
	t_ast_token *prev_tkn
) {
	if (token->type == TKN_GROUP)
	{
		if (prev_tkn->type != TKN_PIPE && prev_tkn->type != TKN_DELIM
			&& prev_tkn->type != TKN_SEP)
			return (msh_ast_errd(AST_ERROR_SYNTAX, (void *)
					msh_syntax_error_impl(token, "("), false));
	}
	else if ((token->type == TKN_PIPE || token->type == TKN_DELIM)
		&& prev_tkn->type != TKN_WORD && prev_tkn->type != TKN_STRING
		&& prev_tkn->type != TKN_GROUP && prev_tkn->type != TKN_SEP
		&& prev_tkn->type != TKN_REDIR && prev_tkn->type != TKN_SUBST)
		return (msh_ast_errd(AST_ERROR_SYNTAX, (void *)msh_syntax_error(
					prev_tkn), false));
	else if (prev_tkn->type == TKN_GROUP && (token->type == TKN_SUBST
			|| token->type == TKN_WORD || token->type == TKN_STRING))
		return (msh_ast_errd(AST_ERROR_SYNTAX, (void *)msh_syntax_error(
					token), false));
	return (msh_ast_ok());
}

t_ast_error	msh_ast_sanitize_token_word_before(
	t_minishell *msh,
	t_list *current,
	t_ast_token *prev_tkn
) {
	static const t_ast_token_type	types[] = {
		TKN_PIPE, TKN_DELIM, TKN_SEMISEMI, TKN_GROUP, TKN_WORD,
		TKN_STRING, TKN_SUBST};
	int								i;
	t_ast_token						*curr_tkn;
	t_ast_error						err;

	msh_log(msh, MSG_DEBUG_TOKEN_SANITIZER, "sanitize_check_word_before\n");
	if (!current || !current->content || !prev_tkn)
		return (msh_ast_ok());
	curr_tkn = current->content;
	i = -1;
	err = msh_ast_ok();
	while (!err.type && ++i < (int)(sizeof(types) / sizeof(types[0])))
	{
		if (curr_tkn->type == types[i])
		{
			if (curr_tkn->type == TKN_DELIM && curr_tkn->kind == DELIM_NEWLINE)
				break ;
			err = msh_ast_sanitize_token_check_prev(msh, current, curr_tkn,
					prev_tkn);
		}
	}
	return (err);
}
