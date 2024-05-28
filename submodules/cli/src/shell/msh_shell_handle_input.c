/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_shell_handle_input.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 05:22:17 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/28 12:02:03 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/ast/lexer.h>
#include <msh/cli/input.h>
#include <msh/cli/shell.h>
#include <msh/exec/exec.h>
#include <msh/env.h>
#include <stdio.h>
#include <stdlib.h>

#define REINPUT_ALLOC_ERROR ": error while joining secondary input"

static t_ast_error	msh_reinput(t_minishell *msh, t_ast_lexer *lexer,
						const char *prompt)
{
	char	*line;

	line = msh_input_forked(msh, prompt);
	lexer->input = ft_strjoins(2, "", 0b10 + msh->interactive,
			lexer->input, line);
	if (!lexer->input)
		return (msh_ast_errd(AST_ERROR_ALLOC, REINPUT_ALLOC_ERROR, false));
	return (msh_ast_ok());
}

static t_list	*msh_build_ast_tokens(t_minishell *msh, char *line,
					char *prompt)
{
	t_ast_lexer	lexer;
	t_ast_error	err;

	lexer = msh_ast_lexer_root(msh, line);
	err = msh_ast_tokenize(&lexer);
	while (err.retry)
	{
		msh_ast_lexer_debug(msh, "error type %d, reprompting...\n", err.type);
		msh->execution_context.line++;
		lexer.cursor = 0;
		err = msh_reinput(msh, &lexer, prompt);
		if (err.type != AST_ERROR_NONE)
			break ;
		err = msh_ast_tokenize(&lexer);
	}
	if (err.type != AST_ERROR_NONE)
	{
		msh_ast_error_print(msh, err);
		if (lexer.tokens)
			ft_lst_free(&lexer.tokens, (t_lst_dealloc) msh_ast_token_free);
	}
	if (lexer.input)
		free((char *)lexer.input);
	return (lexer.tokens);
}

static void	msh_handle_ast(t_minishell *msh, char *line)
{
	t_list		*tokens;
	t_list		*save;
	t_ast_token	*token;
	char		*prompt;

	prompt = msh_env_value(msh, "PS2");
	if (!prompt || !*prompt)
		prompt = ENV_DEFAULT_PS2;
	tokens = msh_build_ast_tokens(msh, line, prompt);
	if (!tokens)
		return ;
	save = tokens;
	while (tokens && msh->flags.debug_tokenizer)
	{
		if (save == tokens)
			printf("Token list: \n");
		token = (t_ast_token *) tokens->content;
		if (token)
			msh_ast_token_print(msh, token);
		tokens = tokens->next;
	}
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
		msh->execution_context.exit_code = 1;
		return ;
	}
	printf("line: '%s'\n", line);
	msh_handle_ast(msh, line);
	// if (*line && msh->interactive)
		// add_history(line);
	// msh_debug_exec(msh, line);
}
