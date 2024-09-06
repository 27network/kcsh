/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_shell_handle_input.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 05:22:17 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/03 20:40:56 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/ast/builder.h>
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

static bool	msh_handle_ast(t_minishell *msh, t_input_result input,
				t_ast_node **result)
{
	t_list	*tokens;
	char	*prompt;
	char	*line;

	line = ft_strdup(input.buffer);
	if (!line)
		msh_error(msh, "allocation error while duplicating input\n");
	if (!line)
		return (false);
	input.buffer = line;
	msh_env_set_if_not(msh, "PS2", ENV_DEFAULT_PS2, 0);
	prompt = msh_env_value(msh, "PS2");
	if (!prompt || !*prompt)
		prompt = ENV_DEFAULT_PS2;
	*result = NULL;
	if (!msh_ast_lex(msh, input, prompt, &tokens))
		return (false);
	msh_dump_tokens(msh, tokens);
	if (!msh_ast_create(msh, tokens, result))
		ft_lst_free(&tokens, (t_lst_dealloc) msh_ast_token_free);
	if (*result && msh->flags.debug_ast)
		msh_ast_node_print(msh, *result);
	return (*result != NULL);
}

static void	msh_takeoff(t_minishell *msh, t_input_result input)
{
	t_ast_node	*ast;

	if (msh_handle_ast(msh, input, &ast) && !msh->forked && !msh->flags
		.debug_tokenizer && !msh->flags.debug_sanitizer
		&& !msh->flags.debug_ast)
	{
		if (!msh_exec_wrap(msh, ast))
			msh->execution_context.exit_code = 1;
	}
	else
		msh->execution_context.exit_code = 1;
	msh_ast_node_free(ast);
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
		msh->execution_context.exit_code = 0;
	if (!input.buffer)
		return ;
	msh_handle_history(input, false);
	msh_takeoff(msh, input);
	ft_strdel((char **) &input.buffer);
}
