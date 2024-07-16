/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_shell_handle_input.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 05:22:17 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/16 15:42:42 by kiroussa         ###   ########.fr       */
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

void	msh_handle_history(t_input_result input, bool should_pop)
{
	size_t	size;
	bool	change;

	if (input.type != INPUT_OK)
		return ;
	if (!input.buffer || !*input.buffer)
		return ;
	size = ft_strlen(input.buffer);
	change = (size && input.buffer[size - 1] == '\n');
	if (change)
		input.buffer[size - 1] = 0;
	if (should_pop)
		msh_history_modify_last(input.buffer);
	else
		msh_history_push(input.buffer);
	if (change)
		input.buffer[size - 1] = '\n';
}

static void	msh_dump_tokens(t_minishell *msh, t_list *tokens)
{
	t_ast_token	*token;

	printf("\n>>> Token list: \n");
	if (!tokens)
		return ;
	while (tokens)
	{
		token = (t_ast_token *) tokens->content;
		if (token)
			msh_ast_token_print(msh, token);
		tokens = tokens->next;
	}
	printf("\n");
}

static void	msh_handle_ast(t_minishell *msh, t_input_result input)
{
	t_list	*tokens;
	char	*prompt;
	char	*line;

	line = ft_strdup(input.buffer);
	if (!line)
		msh_error(msh, "error while duplicating input\n");
	if (!line)
		return ;
	input.buffer = line;
	prompt = msh_env_value(msh, "PS2");
	if (!prompt || !*prompt)
		prompt = ENV_DEFAULT_PS2;
	tokens = msh_ast_lex(msh, input, prompt);
	if (!tokens)
		return ;
	if (msh->flags.debug_tokenizer)
		msh_dump_tokens(msh, tokens);
	ft_lst_free(&tokens, (t_lst_dealloc) msh_ast_token_free);
}

static void	msh_debug_exec(t_minishell *msh, char *line)
{
	char	**array;
	size_t	i;
	int		ret;

	array = ft_splits(line, ENV_DEFAULT_IFS);
	if (!array)
		return ;
	if (*array)
	{
		ret = msh_exec_simple(msh, array);
		msh->execution_context.exit_code = ret;
	}
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
	}
	if (input.buffer && !*input.buffer)
		ft_strdel((char **) &input.buffer);
	if (!input.buffer)
		return ;
	msh_handle_history(input, false);
	msh_handle_ast(msh, input);
	if (!msh->forked && !msh->flags.debug_tokenizer)
		msh_debug_exec(msh, input.buffer);
	ft_strdel((char **) &input.buffer);
}
