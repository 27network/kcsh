/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_lex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:44:37 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/28 14:31:03 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <ft/print.h>
#include <msh/ast/lexer.h>
#include <msh/ast/sanitizer.h>
#include <msh/cli/history.h>
#include <msh/cli/input.h>
#include <msh/cli/shell.h>
#include <msh/log.h>
#include <stdlib.h>

#define REINPUT_ALLOC_ERROR ": error while joining secondary input"

void	msh_handle_history(t_input_result input, bool should_pop);

static t_ast_error	msh_reinput(t_minishell *msh, t_ast_lexer *lexer,
						const char *prompt, t_input_result *update)
{
	const t_input_result	result = msh_input(msh, prompt);

	*update = result;
	if (msh->forked || result.type == INPUT_INTERRUPTED)
		return (msh_ast_errd(AST_ERROR_CANCEL, NULL, false));
	if (result.type == INPUT_ERROR)
	{
		if (result.buffer)
			ft_strdel((char **) &result.buffer);
		*update = result;
		return (msh_ast_errd(AST_ERROR_INPUT, result.buffer, false));
	}
	if (result.buffer)
		lexer->input = ft_strjoins(2, "", 0b11, lexer->input, result.buffer);
	*update = result;
	if (!lexer->input)
		return (msh_ast_errd(AST_ERROR_ALLOC, REINPUT_ALLOC_ERROR, false));
	msh_handle_history((t_input_result){.buffer = (char *)lexer->input,
		.type = INPUT_OK}, true);
	return (msh_ast_ok());
}

// Just free it when forked since we don't want the double output
void	msh_ast_error_free(t_ast_error error);

// We have lines available, let's make the most of it ;)
void	msh_dump_tokens(t_minishell *msh, t_list *tokens);

static bool	msh_lex_handle_errors(t_ast_lexer *state, t_input_result input,
					t_ast_error err, t_list **result)
{
	ft_strdel((char **) &state->input);
	*result = NULL;
	if (state->msh->forked)
	{
		ft_lst_free(&state->tokens, (t_lst_dealloc) msh_ast_token_free);
		msh_ast_error_free(err);
		return (false);
	}
	if (err.type != AST_ERROR_NONE)
	{
		msh_ast_error_print(state->msh, err);
		if (input.type == INPUT_EOF)
			msh_error(state->msh, "syntax error: unexpected end of file\n");
	}
	if (err.type != AST_ERROR_NONE)
		return (err.type == AST_ERROR_CANCEL);
	msh_dump_tokens(state->msh, state->tokens);
	err = msh_ast_sanitize_tokens(state->msh, &state->tokens);
	if (err.type == AST_ERROR_NONE)
		*result = state->tokens;
	else
		msh_ast_error_print(state->msh, err);
	if (err.type != AST_ERROR_NONE && state->tokens)
		ft_lst_free(&state->tokens, (t_lst_dealloc) msh_ast_token_free);
	return (err.type == AST_ERROR_NONE);
}

bool	msh_ast_lex(t_minishell *msh, t_input_result input,
				char *prompt, t_list **result)
{
	t_ast_lexer	lexer;
	t_ast_error	err;

	lexer = msh_ast_lexer_root(msh, input.buffer);
	while (1)
	{
		err = msh_ast_tokenize(&lexer);
		if (!err.retry || input.type == INPUT_EOF || msh->forked
			|| err.type == AST_ERROR_NONE)
			break ;
		msh_ast_error_free(err);
		msh->execution_context.line++;
		lexer.cursor = 0;
		err = msh_reinput(msh, &lexer, prompt, &input);
		if (err.type != AST_ERROR_NONE || msh->forked)
			break ;
	}
	return (msh_lex_handle_errors(&lexer, input, err, result));
}
