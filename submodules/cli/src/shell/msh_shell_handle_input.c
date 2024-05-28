/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_shell_handle_input.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 05:22:17 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/28 21:10:58 by kiroussa         ###   ########.fr       */
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

static t_ast_error	msh_reinput(t_minishell *msh, t_ast_lexer *lexer,
						const char *prompt)
{
	const t_input_result	result = msh_input_forked(msh, prompt);

	if (result.type == INPUT_ERROR)
	{
		if (result.buffer)
			ft_strdel((char **) &result.buffer);
		return (msh_ast_errd(AST_ERROR_INPUT, result.buffer, false));
	}
	if (result.buffer)
		lexer->input = ft_strjoins(2, "", 0b11 + msh->interactive,
				lexer->input, result.buffer);
	if (!lexer->input)
		return (msh_ast_errd(AST_ERROR_ALLOC, REINPUT_ALLOC_ERROR, false));
	return (msh_ast_ok());
}

static t_list	*msh_build_ast_tokens(t_minishell *msh, t_input_result input,
					char *prompt)
{
	t_ast_lexer	lexer;
	t_ast_error	err;

	lexer = msh_ast_lexer_root(msh, input.buffer);
	while (1)
	{
		err = msh_ast_tokenize(&lexer);
		if (err.type == AST_ERROR_NONE)
			break ;
		if (!err.retry)
			break ;
		msh_ast_lexer_debug(msh, "error type %d, reprompting...\n", err.type);
		msh->execution_context.line++;
		lexer.cursor = 0;
		err = msh_reinput(msh, &lexer, prompt);
		if (err.type != AST_ERROR_NONE)
			break ;
	}
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

void	msh_shell_handle_input(t_minishell *msh, t_input_result input)
{
	if (input.type == INPUT_ERROR)
	{
		ft_strdel((char **) &input.buffer);
		msh->execution_context.exit_code = 1;
		msh_error(msh, "error while reading input\n");
		return ;
	}
	printf("line: '%s'\n", input.buffer);
	msh_history_push(input.buffer);
	msh_handle_ast(msh, input);
	// if (*line && msh->interactive)
		// add_history(line);
	// msh_debug_exec(msh, line);
}
