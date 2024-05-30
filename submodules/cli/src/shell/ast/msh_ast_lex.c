/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_lex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:44:37 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/30 19:23:37 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <ft/print.h>
#include <msh/ast/lexer.h>
#include <msh/cli/history.h>
#include <msh/cli/input.h>
#include <msh/cli/shell.h>
#include <stdlib.h>

#define REINPUT_ALLOC_ERROR ": error while joining secondary input"

void	msh_handle_history(t_input_result input, bool should_pop);

static t_ast_error	msh_reinput(t_minishell *msh, t_ast_lexer *lexer,
						const char *prompt, bool *eof)
{
	const t_input_result	result = msh_input_forked(msh, prompt);
	const char				*save;

	if (msh->forked || result.type == INPUT_INTERRUPTED)
		return (msh_ast_errd(AST_ERROR_GENERIC, NULL, false));
	if (result.type == INPUT_ERROR)
	{
		if (result.buffer)
			ft_strdel((char **) &result.buffer);
		return (msh_ast_errd(AST_ERROR_INPUT, result.buffer, false));
	}
	msh_handle_history(result, true);
	*eof = (result.type == INPUT_EOF);
	if (result.buffer)
	{
		save = lexer->input;
		lexer->input = ft_strjoin(lexer->input, result.buffer);
		free((char *) save);
		ft_strdel((char **) &result.buffer);
	}
	if (!lexer->input)
		return (msh_ast_errd(AST_ERROR_ALLOC, REINPUT_ALLOC_ERROR, false));
	return (msh_ast_ok());
}

t_list	*msh_ast_lex(t_minishell *msh, t_input_result input,
				char *prompt)
{
	t_ast_lexer	lexer;
	t_ast_error	err;
	bool		eof;

	printf(">>> Built AST tokens\n");
	eof = false;
	lexer = msh_ast_lexer_root(msh, input.buffer);
	while (1)
	{
		err = msh_ast_tokenize(&lexer);
		if (err.type == AST_ERROR_NONE)
			break ;
		if (!err.retry || eof)
			break ;
		msh_ast_lexer_debug(msh, "error type '%s', reprompting...\n",
			msh_ast_strerror(err.type));
		msh->execution_context.line++;
		lexer.cursor = 0;
		err = msh_reinput(msh, &lexer, prompt, &eof);
		if (err.type != AST_ERROR_NONE)
			break ;
	}
	printf(">>> Finished building AST tokens\n");
	if (eof || msh->forked)
		ft_lst_free(&lexer.tokens, (t_lst_dealloc) msh_ast_token_free);
	if (eof)
		printf("error: unexpected EOF\n");
	if (lexer.input)
		ft_strdel((char **) &lexer.input);
	return (lexer.tokens);
}
