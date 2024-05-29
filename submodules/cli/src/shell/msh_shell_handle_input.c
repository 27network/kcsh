/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_shell_handle_input.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 05:22:17 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/30 00:25:49 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/ast/lexer.h>
#include <msh/cli/history.h>
#include <msh/cli/input.h>
#include <msh/cli/shell.h>
#include <msh/exec/exec.h>
#include <msh/env.h>
#include <msh/log.h>
#include <stdio.h>
#include <stdlib.h>

#define REINPUT_ALLOC_ERROR ": error while joining secondary input"

static void	msh_handle_history(t_input_result input, bool should_pop)
{
	size_t	size;
	bool	change;

	printf("adding to history\n");
	if (input.type != INPUT_OK)
		return ;
	if (!input.buffer || !*input.buffer)
		return ;
	if (should_pop)
		msh_history_pop();
	size = ft_strlen(input.buffer);
	change = (size && input.buffer[size - 1] == '\n');
	if (change)
		input.buffer[size - 1] = 0;
	msh_history_push(input.buffer);
	if (change)
		input.buffer[size - 1] = '\n';
}

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
	msh_handle_history(result, /*true*/ false);
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

static t_list	*msh_build_ast_tokens(t_minishell *msh, t_input_result input,
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
		msh_ast_lexer_debug(msh, "error type %d, reprompting...\n", err.type);
		msh->execution_context.line++;
		lexer.cursor = 0;
		err = msh_reinput(msh, &lexer, prompt, &eof);
		if (err.type != AST_ERROR_NONE)
			break ;
	}
	printf(">>> Finished building AST tokens\n");
	if (eof)
		printf("error: unexpected EOF\n");
	if (lexer.input)
		ft_strdel((char **) &lexer.input);
	return (lexer.tokens);
}

static void	msh_handle_ast(t_minishell *msh, t_input_result input)
{
	t_list		*tokens;
	t_list		*save;
	t_ast_token	*token;
	char		*prompt;

	prompt = msh_env_value(msh, "PS2");
	if (!prompt || !*prompt)
		prompt = ENV_DEFAULT_PS2;
	tokens = msh_build_ast_tokens(msh, input, prompt);
	if (!tokens)
		return ;
	save = tokens;
	while (tokens && msh->flags.debug_tokenizer)
	{
		if (save == tokens)
			printf("\n>>> Token list: \n");
		token = (t_ast_token *) tokens->content;
		if (token)
			msh_ast_token_print(msh, token);
		tokens = tokens->next;
	}
	printf("\n");
	ft_lst_free(&save, (t_lst_dealloc) msh_ast_token_free);
}

/*
__attribute__((unused))
static void	msh_debug_exec(t_minishell *msh, char *line)
{
	char	**array;
	size_t	i;
	int		ret;

	array = ft_splits(line, " \t\n");
	if (!array)
		return ;
	ret = msh_exec_simple(msh, array);
	msh->execution_context.exit_code = ret;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
*/

void	msh_shell_handle_input(t_minishell *msh, t_input_result input)
{
	if (input.type == INPUT_ERROR)
	{
		ft_strdel((char **) &input.buffer);
		msh->execution_context.exit_code = 1;
		msh_error(msh, "error while reading input\n");
		return ;
	}
	if (!input.buffer || !*input.buffer)
		return ;
	msh_handle_history(input, false);
	(void) msh_handle_ast;
	// msh_handle_ast(msh, input);
}
